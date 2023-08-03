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

class Game
{
    private:
        //Name and size
        int _GameWidth;
        int _GameHeight;
        std::string _GameTitle;
        int _MixChannels;
        
        //internal procedures
        void _GameInitSDL();
        bool _ChangeState();
        
        //Mandatory
        Game(std::string, int, int);
        static Game* _GameInstance;
        SDL_Window* _GameWindow = nullptr;
        SDL_Renderer* _GameRenderer = nullptr;
        State* _GameState = nullptr;
        std::stack<std::unique_ptr<State>> StateStack;

        int _FrameStart;
        float _Dt;
        void _CalculateDt();


    public:
        //Copy prevention
        Game(const Game&) = delete;
        void operator=(Game &game)= delete;

        //Mandatory
        ~Game();
        void Run();
        void Push(State*);
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& Instance();
        float GetDt();

};

#endif//LICHEN_GAME
