#include "../lib/CameraFollower.hpp"
#include "../lib/Engine.hpp"

CameraFollower::CameraFollower(GameObject& GameObj)
: Component(GameObj)
{
    Offset = Vector2(0,0);
}

void CameraFollower::Update(float Dt)
{
    Parent.Box.x = Engine::Instance().GetState().Cam.Position.x + Offset.x;
    Parent.Box.y = Engine::Instance().GetState().Cam.Position.y + Offset.y;
}

void CameraFollower::Render()
{
}

void CameraFollower::Start()
{
}

bool CameraFollower::Is(std::string Type)
{
    return (Type == "CameraFollower");
}