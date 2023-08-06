#ifndef LICHEN_SPRITE
#define LICHEN_SPRITE

#include <string>

#include "SDL2/SDL_image.h"

#include "GameObject.hpp"
#include "Component.hpp"
#include "Settings.hpp"
#include "Timer.hpp"

class Sprite : public Component
{
    private:
        SDL_Texture* _SpriteTexture;
        int _SpriteWidth;
        int _SpriteHeight;
        SDL_Rect _ClipRect;
        Vector2 _Scale;
        int _FrameCount;
        int _CurrFrame;
        float _TimeElapsed;
        float _FrameTime;
        Flip _Orientation;
        Vector2 _Parallax;

    public:
        bool Loop;
        Timer ToSelfDestruct;
        float LifeTime;

        Sprite(GameObject&);
        Sprite(GameObject&, std::string);
        Sprite(GameObject&, std::string, int, float);
        Sprite(GameObject&, std::string, int, float, float);
        ~Sprite();
        
        void Open(std::string);
        void SetClip(int, int, int, int);
        int GetWidth();
        int GetHeight();
        void SetScale(float, float);
        void SetScale(Vector2);
        Vector2 GetScale();
        void SetParallax(Vector2);
        Vector2 GetParallax();
        bool IsOpen();

        void SetFrame(int);
        void SetFrameCount(int);
        void SetFrameTime(float);
        void SetFlip(Flip);
        Flip GetFlip();
        
        bool Is(std::string);
        void Render();
        void Render(float, float);
        void Render(float, float, float);
        void Start();
        void Update(float);
        
};

#endif//LICHEN_SPRITE