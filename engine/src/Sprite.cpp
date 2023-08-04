#include "../lib/Sprite.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"

Sprite::Sprite(GameObject& GameObj)
: Component(GameObj)
{
    _SpriteTexture = nullptr;
    _Scale = Vector2(1,1);
    _FrameCount = 0;
    _CurrFrame = 0;
    _TimeElapsed = 0;
    _FrameTime = 0;
    _Orientation = Flip::N;
    Loop = true;
    LifeTime = 0;
    ToSelfDestruct.Restart();
}

Sprite::Sprite(GameObject& GameObj, std::string File)
: Sprite(GameObj)
{
    Open(File);
}

Sprite::Sprite(GameObject& GameObj, std::string File, int FrameCount = 1, float FrameTime = 1)
: Sprite(GameObj)
{
    Open(File);
    _FrameCount = FrameCount;
    _FrameTime = FrameTime;
    _SpriteWidth /= FrameCount;
    SetClip(0,0, _SpriteWidth, _SpriteHeight);    
}

Sprite::Sprite(GameObject& GameObj, std::string File, int FrameCount = 1, float FrameTime = 1, float LifeTime = 0)
: Sprite(GameObj)
{
    Open(File);
    _FrameCount = FrameCount;
    _FrameTime = FrameTime;
    _SpriteWidth /= FrameCount;
    SetClip(0,0, _SpriteWidth, _SpriteHeight);
    this->LifeTime = LifeTime;
}

Sprite::~Sprite()
{
}

void Sprite::Open(std::string File)
{
    _SpriteTexture = Resources::GetImage(File);
    if(_SpriteTexture == nullptr)
    {
        Error("Sprite::Open: Image could not be loaded");
    }

    if(SDL_QueryTexture(_SpriteTexture, nullptr, nullptr, &_SpriteWidth, &_SpriteHeight))
    {
        Error("Sprite::Open: QueryTexture failed");
    }
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
    return (_SpriteWidth * _Scale.x);
}

int Sprite::GetHeight()
{
    return (_SpriteHeight * _Scale.y);
}

void Sprite::SetScale(float ScaleX, float ScaleY)
{
    _Scale = Vector2(ScaleX, ScaleY);
}

Vector2 Sprite::GetScale()
{
    return _Scale;
}

bool Sprite::IsOpen()
{
    return (_SpriteTexture != nullptr);
}

void Sprite::SetFrame(int Frame)
{
    _CurrFrame = Frame;
    SetClip(_CurrFrame*_SpriteWidth, 0, _SpriteWidth, _SpriteHeight);
}

void Sprite::SetFrameCount(int FrameCount)
{
    _FrameCount = FrameCount;
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
    SDL_Rect DestinyRect;
    DestinyRect.x = x - Engine::Instance().GetState().Cam.Position.x;
    DestinyRect.y = y - Engine::Instance().GetState().Cam.Position.y;
    DestinyRect.w = _ClipRect.w  * _Scale.x;
    DestinyRect.h = _ClipRect.h * _Scale.y;

    if(SDL_RenderCopyEx(Engine::Instance().GetRenderer(), _SpriteTexture, &_ClipRect, &DestinyRect, Vector2::RadToDeg(Angle), nullptr, (SDL_RendererFlip) _Orientation))
    {
        Error("Sprite::Render: Sprite copy to render device has failed");
    }
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


