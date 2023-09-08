#include "../lib/Sprite.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"

Sprite::Sprite(GameObject& GameObj, std::string File, int FrameCount , int Columns, int Rows, float FrameTime, float LifeTime)
: Component(GameObj)
{
    _SpriteImage = nullptr;
    Open(File);
    _Scale = Vector2(1,1);
    _Parallax = Vector2(1,1);
    _FrameCount = FrameCount;
    _CurrFrame = 0;
    _XFrames = Columns;
    _YFrames = Rows;
    _FrameTime = FrameTime;
    _TimeElapsed = 0;
    SetFrame(_CurrFrame);
    _Orientation = Flip::N;
    Loop = true;
    this->LifeTime = LifeTime;
    ToSelfDestruct.Restart();
    _SpriteColor = Color("#FFFFFFFF");
}

Sprite::Sprite(GameObject& GameObj, std::string File, int FrameCount, int Columns, int Rows)
: Sprite(GameObj, File, FrameCount, Columns, Rows, 0.0f, 0.0f)
{
}

Sprite::Sprite(GameObject& GameObj, std::string File)
: Sprite(GameObj, File, 1, 1, 1)
{
}  

Sprite::~Sprite()
{
    delete _SpriteImage;
}

void Sprite::Open(std::string File)
{
    _SpriteImage = new Image(File);
    _SpriteWidth = _SpriteImage->GetWidth();
    _SpriteHeight = _SpriteImage->GetHeight();
    SetClip(0,0, _SpriteWidth, _SpriteHeight);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    _ClipRect.x = x;
    _ClipRect.y = y;
    _ClipRect.w = w;
    _ClipRect.h = h;
}


int Sprite::GetWidth()
{
    return (_SpriteWidth/_XFrames * _Scale.x);
}

int Sprite::GetHeight()
{
    return (_SpriteHeight/_YFrames * _Scale.y);
}

void Sprite::SetScale(float ScaleX, float ScaleY)
{
    _Scale = Vector2(ScaleX, ScaleY);
}

void Sprite::SetScale(Vector2 Scale)
{
    _Scale = Scale;
}

Vector2 Sprite::GetScale()
{
    return _Scale;
}

void Sprite::SetParallax(Vector2 Parallax)
{
    _Parallax = Parallax;
}

Vector2 Sprite::GetParallax()
{
    return _Parallax;
}

bool Sprite::IsOpen()
{
    return (_SpriteImage != nullptr);
}

void Sprite::SetColor(Color New)
{
    _SpriteImage->SetColor(New);
}

Color Sprite::GetColor()
{
    return _SpriteImage->GetColor();
}

void Sprite::SetFrame(int Frame)
{
    if (Frame >= _FrameCount ) //Just in case someone asks for sprites outside the boundaries
    {
        Error("Sprite::SetFrame: Frame requested exceeds the max number of frames on current texture");
    }
    int Column = Frame % _XFrames, Row = Frame / _XFrames;
    float Width = _SpriteWidth / _XFrames;
    float Height = _SpriteHeight / _YFrames;
    
    SetClip(Column * Width, Row * Height, Width, Height);
}

void Sprite::SetFrameCount(int FrameCount)
{
    _FrameCount = FrameCount;
}

void Sprite::SetColumns(int Columns)
{
    _XFrames = Columns;
}

void Sprite::SetRows(int Rows)
{
    _YFrames = Rows;
}

void Sprite::SetFrameTime(float FrameTime)
{
    _FrameTime = FrameTime;
}

void Sprite::SetFlip(Flip Direction)
{
    _Orientation = Direction;
}

Flip Sprite::GetFlip()
{
    return _Orientation;
}


//Inheritance
bool Sprite::Is(std::string Type)
{
    return ("Sprite" == Type);
}

void Sprite::Render()
{
    Render(Parent.Box.x, Parent.Box.y);
}

void Sprite::Render(float x, float y)
{
    Render(x, y, Parent.Angle);
}

void Sprite::Render(float x, float y, float Angle)
{
    Vector2 Destiny;
    Destiny.x = (x+GetWidth()/2)*_Parallax.x;
    Destiny.y = (y+GetHeight()/2)*_Parallax.y;

    _SpriteImage->Render(Engine::Instance().GetRenderer(),
        Engine::Instance().GetWindow().GetProjection(),
        Destiny, _Scale, _ClipRect, Angle, _Orientation);
}

void Sprite::Start()
{
}

void Sprite::Update(float Dt)
{
    if(LifeTime > 0)
    {
        ToSelfDestruct.Update(Dt);
        if(ToSelfDestruct.Get() >= LifeTime)
        {
            Parent.RequestDelete();
        }
    }

    if (_FrameTime>0)
    {
        _TimeElapsed += Dt;
        if(_TimeElapsed >= _FrameTime && _FrameCount > 1)
        {
            if(Loop == true || _CurrFrame < _FrameCount-1)
            {
                ++_CurrFrame%=_FrameCount;
                SetFrame(_CurrFrame);
            }    
            _TimeElapsed = 0;
        }
    }
}

Shader& Sprite::GetShader()
{
    return _SpriteImage->GetShader();
}

