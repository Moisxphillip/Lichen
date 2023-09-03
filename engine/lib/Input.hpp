#ifndef LICHEN_INPUT
#define LICHEN_INPUT

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

//Engine
#include "Vector2.hpp"

#define K_LEFTARROW SDLK_LEFT
#define K_RIGHTARROW SDLK_RIGHT
#define K_UPARROW SDLK_UP
#define K_DOWNARROW SDLK_DOWN
#define K_ENTER SDLK_RETURN
#define K_SPACE SDLK_SPACE

#define K_W  SDLK_w
#define K_A SDLK_a
#define K_S SDLK_s
#define K_D SDLK_d
#define K_B SDLK_b
#define K_P SDLK_p

#define K_ESC SDLK_ESCAPE
#define M_LEFT SDL_BUTTON_LEFT
#define M_RIGHT SDL_BUTTON_RIGHT

class Input
{
    private:
        Input();
        ~Input();
        static Input* _InputM;
        
        bool _QuitRequested;
        int _UpdateCounter;

        bool _KeyState[416];
        int _KeyUpdate[416];
        
        bool _MouseState[6];
        int _MouseUpdate[6];
        double _MouseX;
        double _MouseY;
        
    public:
        //Copy prevention
        Input(const Input&) = delete;
        void operator=(Input &InputMg)= delete;

        void Update();
        bool QuitRequested();
        static Input& Instance();
        
        bool KeyPress(int);
        bool KeyRelease(int);
        bool IsKeyDown(int);

        bool MousePress(int);
        bool MouseRelease(int);
        bool IsMouseDown(int);
        int GetMouseX();
        int GetMouseY();
        Vector2 MousePosition();

};

#endif//LICHEN_INPUT