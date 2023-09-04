#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Input.hpp"
#include "../lib/Tools.hpp"

#define SOUNDCHANNELS 32

//Set value for singleton class
Engine* Engine::_GameInstance = nullptr;

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

Engine::Engine(std::string Name = "LichenEngine", int Width = 1024, int Height = 600)
{
    _NoVSync = false;
    if(_GameInstance != nullptr)//Report //Error if there is another instance working already
    {
        Error("Engine::Engine: Instance already exists");
        return;
    }
    else //Register window info
    {
        _GameTitle = Name;
        _GameWidth = Width;
        _GameHeight = Height;
        _MixChannels = SOUNDCHANNELS;
        _GameInstance = this;
    }

    _WindowWidth = _GameWidth;
    _WindowHeight = _GameHeight;

    //Init Engine Resources
    
    _GameWindow = new Window(Name, Width, Height, Width, Height, true);
    _GameRenderer = new Renderer;
    _GameRenderer->SetViewPosition(Vector2(0,0));
    _GameRenderer->SetClearColor(Color("#000000"));
    _GameRenderer->SetBlendMode(BlendMode::Add);
    _InitEngineSystems();

    SDL_CreateWindowFrom((void*)_GameWindow->GetGLWindow());
    _FrameStart = SDL_GetTicks();
    _Dt = 0.0f;

    _GameState = nullptr;//new StageState; //Creates a base state for the Engine 
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
    while(!StateStack.empty())
    {
        StateStack.pop();
    }

    delete _GameRenderer;
    delete _GameWindow;

    if(_GameState != nullptr)
    {
        delete _GameState;
        _GameState = nullptr;
    }
    delete _GameInstance;
}

bool Engine::_ChangeState()
{
    if(_GameState != nullptr)
    {
        if(!StateStack.empty())
        {
            StateStack.top()->StatePause();
        }
        StateStack.push(std::unique_ptr<State>(_GameState));
        _GameState = nullptr;
        return true;
    } 
    return false;
}

void Engine::Run()
{   
    _ChangeState();
    while(!StateStack.empty() && !StateStack.top()->QuitRequested())    //Wait for quit state
    {
        if(!StateStack.top()->HasStarted())
        {
            StateStack.top()->StateStart();
        }

        while(!StateStack.top()->PopRequested())
        {
            _GameRenderer->Clear();
            _CalculateDt();
            Input::Instance().Update();
            
            StateStack.top()->StatePhysicsUpdate(1/60);//TODO fix at render device target rate
            StateStack.top()->StateUpdate(GetDt());
            StateStack.top()->StateLateUpdate(GetDt());
            StateStack.top()->StateRender();

            _GameRenderer->Show(_GameWindow->GetGLWindow());
            if (_NoVSync)
            {
                SDL_Delay(Fps(60));//controls the framerate //TODO fix at render device target rate
            }
            if(_ChangeState())
            {
                break;
            }
        }
        if(StateStack.top()->PopRequested())
        {
            bool QuitRequested = StateStack.top()->QuitRequested();
            StateStack.pop();
            if(QuitRequested && !StateStack.empty())
            {
                StateStack.top()->RequestQuit();
            }
            else if(!StateStack.empty() && StateStack.top()->HasStarted())
            {
                StateStack.top()->StateResume();
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

State& Engine::CurrentState()
{
    return *StateStack.top().get();
}

void Engine::Push(State* NewState)
{
    _GameState = NewState;
}

Engine& Engine::Instance()
{
    if(_GameInstance == nullptr) //Only creates a new Engine if there's no other instance of the class currently running
    {
        _GameInstance = new Engine("Lichen", 1024, 600);
    }
    return *_GameInstance;
}

inline void Engine::_CalculateDt()
{
    int FrameEnd = SDL_GetTicks(); //Get Ms count since app start
    _Dt = (FrameEnd - _FrameStart)/1000.0f;//Ms->s is done by the division
    _FrameStart = FrameEnd;
}

inline float Engine::GetDt()
{
    return _Dt;
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