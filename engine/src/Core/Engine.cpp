#include "Core/Engine.hpp"
#include "Core/Resources.hpp"
#include "Core/Input.hpp"
#include "Tools/Tools.hpp"
#include <ctime>

#define SOUNDCHANNELS 48

//Set value for singleton class
Engine* Engine::_GameInstance = nullptr;
XrandF32 Engine::_F32;
XrandU64 Engine::_U64;

void Engine::_InitEngineSystems()
{
    //init SDL
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        Error("Engine::_InitEngineSystems: SDL could not be initialized");
    }
    
    //init Image, Initialized systems = return flags
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) 
                != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        Error("Engine::_InitEngineSystems: IMG could not initialize one of its dependencies");
    }

    //init Audio, Initialized systems = return flags
    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) 
                != (MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3))
    {
        Error("Engine::_InitEngineSystems: Mix could not initialize one or more of its dependencies");
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        Error("Engine::_InitEngineSystems: OpenAudio could not be initialized");
    }
    
    if(Mix_AllocateChannels(_MixChannels) < _MixChannels) //Channel allocation for different audio tracks
    {
        Error("Engine::_InitEngineSystems: Mix_AllocateChannels could not allocate the requested number of channels");
    }

    if(TTF_Init() != 0)
    {
        Error("Engine::_InitEngineSystems: TTF_Init could not be initialized");
    }
}

Engine::Engine(std::string Name, int Width, int Height, int ProjWidth, int ProjHeight, bool VSync)
{
    _F32.seed(static_cast<unsigned long long int>(std::time(nullptr)));
    _U64.seed(static_cast<unsigned long long int>(std::time(nullptr)));

    _VSync = VSync;
    // _VSync = false;

    if(_GameInstance != nullptr)//Report //Error if there is another instance working already
    {
        Error("Engine::Engine: Instance already exists");
        return;
    }
    else //Register window info
    {
        _GameTitle = Name;
        _WindowWidth = Width;
        _WindowHeight = Height;
        _MixChannels = SOUNDCHANNELS;
        _GameInstance = this;
    }


    //Init Engine Resources
    
    _GameWindow = new Window(Name, Width, Height, ProjWidth, ProjHeight, _VSync);
    _GameWidth = _GameWindow->GetProjectionWidth();
    _GameHeight = _GameWindow->GetProjectionHeight();
    _GameRenderer = new Renderer;
    _GameRenderer->SetViewPosition(Vector2(0,0));
    _GameRenderer->SetClearColor(Color("#000000"));
    _GameRenderer->SetBlendMode(BlendMode::Add);
    _InitEngineSystems();

    _FrameStart = glfwGetTime();
    _Dt = 0.0f;
    _PingCounter = 0.0;
    _Ping = true;
    _GameScene = nullptr;//new StageScene; //Creates a base state for the Engine 
}

Engine::~Engine()
{
    //Clear memory used by Resources class
    Resources::FlushContext();

    //Quit SDL subsystems
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();


    //Free last resources
    while(!SceneStack.empty())
    {
        SceneStack.pop();
    }

    delete _GameRenderer;
    delete _GameWindow;

    if(_GameScene != nullptr)
    {
        delete _GameScene;
        _GameScene = nullptr;
    }
    delete _GameInstance;
}

bool Engine::_ChangeScene()
{
    if(_GameScene != nullptr)
    {
        if(!SceneStack.empty())
        {
            SceneStack.top()->ScenePause();
        }
        SceneStack.push(std::unique_ptr<Scene>(_GameScene));
        _GameScene = nullptr;
        return true;
    } 
    return false;
}

void Engine::Run()
{   
    _ChangeScene();

    //These are for timesteps in physics
    const float Step = 0.01f;
    float Accumulator = 0.0f;

    while(!SceneStack.empty() && !SceneStack.top()->QuitRequested())    //Wait for quit state
    {
        if(!SceneStack.top()->HasStarted())
        {
            SceneStack.top()->SceneStart();
            _CalculateDt(); //Will recalculate, maybe solves loading time Dt growth
        }

        while(!SceneStack.top()->PopRequested())
        {
            _GameRenderer->Clear();
            _CalculateDt();
            Input::Instance().Update();
            
            Accumulator+=GetDt();
            while(Accumulator>=Step)
            {
                SceneStack.top()->ScenePhysicsUpdate(Step);
                Accumulator -=(glfwGetTime() - _FrameStart)+Step;
            }
            
            SceneStack.top()->SceneUpdate(GetDt());
            SceneStack.top()->SceneLateUpdate(GetDt());
            SceneStack.top()->SceneRender();

            if(_PingCounter > 1.0)//Easy signal for some applications
            {
                _PingCounter = 0.0;
                _Ping = true;
            }
            else
            {
                _PingCounter+=GetDt();
                _Ping = false;
            }

            _GameRenderer->Show(_GameWindow->GetGLWindow());
            // if (_VSync)
            // {
            //     //TODO make suitable framerate control if needed
            // }
            if(_ChangeScene())
            {
                break;
            }
        }
        if(SceneStack.top()->PopRequested())
        {
            bool QuitRequested = SceneStack.top()->QuitRequested();
            SceneStack.pop();
            if(QuitRequested && !SceneStack.empty())
            {
                SceneStack.top()->RequestQuit();
            }
            else if(!SceneStack.empty() && SceneStack.top()->HasStarted())
            {
                SceneStack.top()->SceneResume();
            }
        }
    }
}

Renderer& Engine::GetRenderer()
{
    return *_GameRenderer;
}

Window& Engine::GetWindow()
{
    return *_GameWindow;
}

Scene& Engine::CurrentScene()
{
    return *SceneStack.top().get();
}

void Engine::Push(Scene* NewScene)
{
    _GameScene = NewScene;
}

Engine& Engine::Instance(std::string Name, int Width, int Height, int ProjWidth, int ProjHeight, bool VSync)
{
    if(_GameInstance == nullptr) //Only creates a new Engine if there's no other instance of the class currently running
    {
        // _GameInstance = new Engine("LichenEngine", 1024, 600); //Penguin
        _GameInstance = new Engine(Name, Width, Height, ProjWidth, ProjHeight, VSync); //Tests
    }
    return *_GameInstance;
}

inline void Engine::_CalculateDt()
{
    double FrameEnd = glfwGetTime(); //Get seconds count count since app start
    _Dt = FrameEnd - _FrameStart;
    _FrameStart = FrameEnd;
}

inline float Engine::GetDt()
{
    return _Dt;
}

bool Engine::GetPing()
{
    return _Ping;
}

Vector2 Engine::GetWindowSize()
{
    return Vector2(_WindowWidth, _WindowHeight);
}

Vector2 Engine::GetRenderSize()
{
    return Vector2(_GameWidth, _GameHeight);
}

int Engine::GetSoundChannels()
{
    return _MixChannels;
}

unsigned int Engine::RandomUint()
{
    return _U64.gen();
}

float Engine::RandomFloat()
{
    return _F32.gen();
}