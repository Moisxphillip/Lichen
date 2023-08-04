#ifndef LICHEN_GAME
#define LICHEN_GAME

//C++ includes
#include <string>
#include <stack>
#include <memory>

//Libraries includes
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

//Engine includes
#include "State.hpp"
#include "Vector2.hpp"

class Engine
{
    private:
        //Name and size
        int _GameWidth;
        int _GameHeight;
        int _WindowWidth;
        int _WindowHeight;
        std::string _GameTitle;
        int _MixChannels;
        bool _NoVSync;

        //internal procedures
        void _GameInitSDL();
        bool _ChangeState();
        
        //Mandatory
        Engine(std::string, int, int);
        static Engine* _GameInstance;
        SDL_Window* _GameWindow = nullptr;
        SDL_Renderer* _GameRenderer = nullptr;
        State* _GameState = nullptr;
        std::stack<std::unique_ptr<State>> StateStack;

        int _FrameStart;
        float _Dt;
        void _CalculateDt();


    public:
        //Copy prevention
        Engine(const Engine&) = delete;
        void operator=(Engine &Engine)= delete;

        //Mandatory
        ~Engine();
        void Run();
        void Push(State*);
        SDL_Renderer* GetRenderer();

        Vector2 GetWindowSize();
        Vector2 GetRenderSize();
        int GetSoundChannels();

        State& GetState();
        static Engine& Instance();
        float GetDt();

};

#endif//LICHEN_GAME
