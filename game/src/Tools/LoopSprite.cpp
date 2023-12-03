#include "Tools/LoopSprite.hpp"

LoopSprite::LoopSprite(GameObject& Parent, std::string File)
: Component(Parent)
{
    _Sprite = new Sprite(Parent, File);
}

LoopSprite::~LoopSprite()
{
    delete _Sprite;
}

Sprite& LoopSprite::GetSprite()
{
    return *_Sprite;
}

void LoopSprite::SetAnimationData(int Columns, int Rows, int Frames, float FrameTime)
{
    _Sprite->SetColumns(Columns);
    _Sprite->SetRows(Rows);
    _Sprite->SetFrameCount(Frames);
    _Sprite->SetFrameSpan(Frames);
    _Sprite->SetFrameStart(0);
    _Sprite->SetFrameTime(FrameTime);
}

void LoopSprite::Update(float Dt)
{
    Parent.Box+=PixelsPerSecond*Dt;
    _Sprite->Update(Dt);
}

#include "Core/Camera.hpp"
#include "Core/Engine.hpp"

void LoopSprite::Render()
{
    int MinX = int(Camera::Position().x) - int(Camera::Position().x) %_Sprite->GetWidth();
    int MinY = int(Camera::Position().y) - int(Camera::Position().y) % _Sprite->GetHeight();
    
    int MaxX = (int(Camera::Position().x)%_Sprite->GetWidth() + Engine::Instance().GetWindow().GetProjectionWidth()) /_Sprite->GetWidth() + 2;
    int MaxY = (int(Camera::Position().y)%_Sprite->GetHeight()+ Engine::Instance().GetWindow().GetProjectionHeight())/_Sprite->GetHeight()+ 2;


    for(int i = -2; i<MaxX; i++)
    {
        for(int j = -2; j<MaxY; j++)
        {
            _Sprite->Render(std::fmod(Parent.Box.x, _Sprite->GetWidth()) + MinX+_Sprite->GetWidth()*i,
                std::fmod(Parent.Box.y, _Sprite->GetHeight()) + MinY + _Sprite->GetHeight()*j);
        }
    }
}
