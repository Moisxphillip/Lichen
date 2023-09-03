#include "../lib/Camera.hpp"
#include "../lib/Settings.hpp"
#include "../lib/Engine.hpp"
#define SPDMAX 300

Vector2 Camera::Position = Vector2(0,0);

Camera::Camera()
{
    _Focus = nullptr;
    Position = Vector2(0,0);
    Speed = Vector2(0, 0);
}

void Camera::Follow(GameObject* Focus)
{
    _Focus = Focus;
    Position = _Focus->Box.Center() - Engine::Instance().GetRenderSize()*0.5;
}

Vector2 Camera::Center()
{
    return Position + Engine::Instance().GetRenderSize()*0.5;
}

void Camera::Unfollow()
{
    _Focus = nullptr;
    Speed = Vector2(0,0);
}

bool Camera::IsFollowing()
{
    return (_Focus != nullptr);
}

void Camera::Update(float Dt)
{
    if(_Focus != nullptr)
    {
        Position  = _Focus->Box.Center() - Engine::Instance().GetRenderSize()*0.5;//focus on the given object

        //Todo camera smoothing around here

        Engine::Instance().GetRenderer().SetViewPosition(Position);
    }
}