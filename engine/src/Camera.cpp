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
    }
    // else //Camera moved freely
    // {
    //     Speed.y += ((InputManager::Instance().IsKeyDown(K_S) | InputManager::Instance().IsKeyDown(K_DOWNARROW)) 
    //     - (InputManager::Instance().IsKeyDown(K_W)| InputManager::Instance().IsKeyDown(K_UPARROW)))* Dt * 100;
    //     Speed.x += ((InputManager::Instance().IsKeyDown(K_D) | InputManager::Instance().IsKeyDown(K_RIGHTARROW))
    //     - (InputManager::Instance().IsKeyDown(K_A)| InputManager::Instance().IsKeyDown(K_LEFTARROW)))* Dt * 100;
        
    //     (InputManager::Instance().KeyPress(K_B) ? Speed = Vector2(0,0):Speed);
    //     Position+= Speed*Dt;

    //     //Speed limiters
    //     (Speed.x > SPDMAX ? Speed.x = SPDMAX:0);
    //     (Speed.x < -SPDMAX ? Speed.x = -SPDMAX:0);
    //     (Speed.y > SPDMAX ? Speed.y = SPDMAX:0);
    //     (Speed.y < -SPDMAX ? Speed.y = -SPDMAX:0);
    // }
}