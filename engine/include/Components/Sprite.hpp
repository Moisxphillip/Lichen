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

        Sprite(GameObject& Parent, std::string Path,int FrameCount, int Columns, int Rows, float FrameTime, float LifeTime);
        Sprite(GameObject& Parent, std::string Path,int FrameCount, int Columns, int Rows, float FrameTime);
        Sprite(GameObject& Parent, std::string Path, int FrameCount, int Columns, int Rows);
        Sprite(GameObject& Parent, std::string Path);
        ~Sprite();
        
        void Open(std::string Path);
        void SetClip(int X, int Y, int W, int H);
        int GetWidth();
        int GetHeight();
        int GetCurrentFrame();
        void SetScale(float ScaleX, float ScaleY);
        void SetScale(Vector2 Scale);
        Vector2 GetScale();
        void SetParallax(Vector2 Parallax);
        Vector2 GetParallax();
        bool IsOpen();

        void SetColor(Color Colour);
        void SetAddColor(Color Colour);
        Color GetColor();
        void SetFrame(int Frame);
        void SetFrameSpan(int Span);
        void SetFrameStart(int Start);
        void SetColumns(int Columns);
        void SetRows(int Rows);
        void SetFrameCount(int FrameCount);
        void SetFrameTime(float FrameTime);
        void SetFlip(Flip F);
        Flip GetFlip();

        void Render();
        void Render(float X, float Y);
        void Render(float X, float Y, float Angle);
        void Start();
        void Update(float Dt);
        Shader& GetShader();
        
};

#endif//LICHEN_SPRITE