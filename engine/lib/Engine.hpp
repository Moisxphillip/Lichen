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

#include "GL/glew.h"
#include "GLFW/glfw3.h"


//Engine includes
#include "State.hpp"
#include "Vector2.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

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
        bool _VSync;

        //internal procedures
        void _InitEngineSystems();
        bool _ChangeState();
        
        //Mandatory
        Engine(std::string, int, int, int=0, int=0, bool=true);
        static Engine* _GameInstance;
        Window* _GameWindow = nullptr;
        SDL_Window* _SDLWindow = nullptr;
        Renderer* _GameRenderer = nullptr;
        
        State* _GameState = nullptr;
        std::stack<std::unique_ptr<State>> StateStack;

        double _FrameStart;
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
        Renderer& GetRenderer();
        Window& GetWindow();

        Vector2 GetWindowSize();
        Vector2 GetRenderSize();
        int GetSoundChannels();

        State& CurrentState();
        static Engine& Instance();
        float GetDt();

};

#endif//LICHEN_GAME
