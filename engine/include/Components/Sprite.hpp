#ifndef LICHEN_SPRITE
#define LICHEN_SPRITE

#include <string>

#include "Core/GameObject.hpp"
#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Tools/Tools.hpp"
#include "Graphics/Image.hpp"


class Sprite : public Component
{
    private:
        Image* _SpriteImage;
        int _SpriteWidth;
        int _SpriteHeight;
        ___ImageRect _ClipRect;
        Vector2 _Scale;
        int _XFrames;
        int _YFrames;
        int _FrameCount;
        int _FrameSpan;
        int _FrameStart;
        int _CurrFrame;
        float _TimeElapsed;
        float _FrameTime;
        Flip _Orientation;
        Vector2 _Parallax;
        Color _SpriteColor;

    public:
        bool Loop;
        Timer ToSelfDestruct;
        float LifeTime;

        Sprite(GameObject&, std::string, int, int, int, float, float);
        Sprite(GameObject&, std::string, int, int, int);
        Sprite(GameObject&, std::string);
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

        void SetColor(Color Colour);
        Color GetColor();
        void SetFrame(int Frame);
        void SetFrameSpan(int Span);
        void SetFrameStart(int Start);
        void SetColumns(int);
        void SetRows(int);
        void SetFrameCount(int);
        void SetFrameTime(float);
        void SetFlip(Flip);
        Flip GetFlip();

        void Render();
        void Render(float, float);
        void Render(float, float, float);
        void Start();
        void Update(float);
        Shader& GetShader();
        
};

#endif//LICHEN_SPRITE