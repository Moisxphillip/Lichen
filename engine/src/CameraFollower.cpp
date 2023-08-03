#include "../lib/CameraFollower.hpp"
#include "../lib/Game.hpp"

CameraFollower::CameraFollower(GameObject& GameObj)
: Component(GameObj)
{
    Offset = Vector2(0,0);
}

void CameraFollower::Update(float Dt)
{
    GameObjAssoc.Box.x = Game::Instance().GetState().Cam.Position.x + Offset.x;
    GameObjAssoc.Box.y = Game::Instance().GetState().Cam.Position.y + Offset.y;
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