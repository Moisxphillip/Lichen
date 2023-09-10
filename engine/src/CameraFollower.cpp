#include "../lib/CameraFollower.hpp"
#include "../lib/Engine.hpp"

CameraFollower::CameraFollower(GameObject& GameObj)
: Component(GameObj)
{
    Offset = Vector2(0,0);
    _Type = ComponentType::CameraFollower;
}

void CameraFollower::LateUpdate(float Dt)
{
    Parent.Box.x = Engine::Instance().CurrentState().Cam.Position().x + Offset.x;
    Parent.Box.y = Engine::Instance().CurrentState().Cam.Position().y + Offset.y;
}