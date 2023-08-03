#include "../lib/Game.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Input.hpp"
#include "../lib/Tools.hpp"

#define SOUNDCHANNELS 32

//Set value for singleton class
Game* Game::_GameInstance = nullptr;

void Game::_GameInitSDL()
{
    //init SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        //Error("Game::_GameInitSDL: SDL could not be initialized");
    }
    
    //init Image, Initialized systems = return flags
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) 
                != (IMG_INIT_JPG | IMG_INIT_PNG))
    {
        //Error("Game::_GameInitSDL: IMG could not initialize one of its dependencies");
    }

    //init Audio, Initialized systems = return flags
    if(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) 
                != (MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3))
    {
        //Error("Game::_GameInitSDL: Mix could not initialize one of its dependencies");
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        //Error("Game::_GameInitSDL: OpenAudio could not be initialized");
    }
    
    if(Mix_AllocateChannels(_MixChannels) < _MixChannels) //Channel allocation for different audio tracks
    {
        //Error("Game::_GameInitSDL: Mix_AllocateChannels could not allocate the requested number of channels");
    }

    if(TTF_Init() != 0)
    {
        //Error("Game::_GameInitSDL: TTF_Init could not be initialized");
    }
}

Game::Game(std::string Name = "LichenEngine", int Width = 1024, int Height = 600)
{
    if(_GameInstance != nullptr)//Report //Error if there is another instance working already
    {
        //Error("Game::Game: Instance already exists");
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

    //Init SDL Resources
    _GameInitSDL();

    //Window creation
    _GameWindow = SDL_CreateWindow(_GameTitle.c_str(), SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, _GameWidth, _GameHeight, SDL_WINDOW_SHOWN);
    if(_GameWindow == nullptr)
    {
        //Error("Game::Game: Window could not be created");   
    }
    
    //Renderer creation
    //-1 allows SDL to choose the most appropriate render drive
    _GameRenderer = SDL_CreateRenderer(_GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(_GameRenderer == nullptr) 
    {
        //Error("Game::Game: Renderer could not be created");   
    }

    _FrameStart = SDL_GetTicks();
    _Dt = 0.0f;

    _GameState = nullptr;//new StageState; //Creates a base state for the game 
}

Game::~Game()
{
    //Clear memory used by Resources class
    Resources::FlushContext();

    //Quit SDL subsystems
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(_GameRenderer);
    SDL_DestroyWindow(_GameWindow);
    SDL_Quit();
    
    //Free last resources
    while(!StateStack.empty())
    {
        StateStack.pop();
    }

    if(_GameState != nullptr)
    {
        delete _GameState;
        _GameState = nullptr;
    }
    delete _GameInstance;
}

bool Game::_ChangeState()
{
    if(_GameState != nullptr)
    {
        if(!StateStack.empty())
        {
            StateStack.top()->Pause();
        }
        StateStack.push(std::unique_ptr<State>(_GameState));
        _GameState = nullptr;
        return true;
    } 
    return false;
}

void Game::Run()
{   
    _ChangeState();
    while(!StateStack.empty() && !StateStack.top()->QuitRequested())    //Wait for quit state
    {
        if(!StateStack.top()->HasStarted())
        {
            StateStack.top()->Start();
        }
        else
        {
            StateStack.top()->Resume();
        }

        while(!StateStack.top()->PopRequested())
        {
            _CalculateDt();
            Input::Instance().Update();
            StateStack.top()->Update(GetDt());//Calls update for all GameObject inside a scene
            StateStack.top()->Render(); //Calls render for all GameObject...
            SDL_RenderPresent(_GameRenderer);//Presents the new rendered stuff on screen
            SDL_Delay(Fps(30));//controls the framerate
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
        }
    } 
    
}

SDL_Renderer* Game::GetRenderer()
{
    return _GameRenderer;
}

State& Game::GetState()
{
    return *StateStack.top().get();
}

void Game::Push(State* NewState)
{
    _GameState = NewState;
}

Game& Game::Instance()
{
    if(_GameInstance == nullptr) //Only creates a new Game if there's no other instance of the class currently running
    {
        _GameInstance = new Game("Lichen", 1024, 600);
    }
    return *_GameInstance;
}

inline void Game::_CalculateDt()
{
    int FrameEnd = SDL_GetTicks(); //Get Ms count since app start
    _Dt = (FrameEnd - _FrameStart)/1000.0f;//Ms->s is done by the division
    _FrameStart = FrameEnd;
}

inline float Game::GetDt()
{
    return _Dt;
}