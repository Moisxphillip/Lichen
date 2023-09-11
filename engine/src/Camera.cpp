#include <algorithm>
#include "../lib/Camera.hpp"
#include "../lib/Settings.hpp"
#include "../lib/Engine.hpp"

Vector2 Camera::_Position = Vector2(0.0f,0.0f);

Camera::Camera()
: _Velocity(0.0f,0.0f), 
_RectBounds(0.0f,0.0f,100.0f,100.0f),
_CircBounds(0.0f,0.0f,50.0f),
_MaxSpeed(100.0f),
_Acceleration(200.0f),
_CurrentMode(CameraMode::Fixed),
_CurrentForm(CameraFormat::Rectangle)
{
    _Focus = nullptr;
    SetRectangleBounds(Rectangle(0.0f,0.0f,200.0f,160.0f));
    _Position = Vector2(0,0);
}

void Camera::Follow(GameObject* Focus)
{
    _Focus = Focus;
    // _Position = _Focus->Box.Center() - Engine::Instance().GetRenderSize()*0.5;
}

Vector2 Camera::Center()
{
    return _Position + Engine::Instance().GetRenderSize()*0.5f;
}

Vector2 Camera::Position()
{
    return _Position;
}

void Camera::Unfollow()
{
    _Focus = nullptr;
}

bool Camera::IsFollowing()
{
    return (_Focus != nullptr);
}

void Camera::SetCameraMode(CameraMode New)
{
    _CurrentMode = New;
}

void Camera::SetCameraFormat(CameraFormat New)
{
    _CurrentForm = New;
}
        
void Camera::SetRectangleBounds(Rectangle Base)
{
    _RectBounds.x = Base.x-Base.w/2;
    _RectBounds.y = Base.y-Base.h/2;
    _RectBounds.Redimension(Base.Dimensions());
}

void Camera::SetCircleBounds(Circle Base)
{
    _CircBounds = Base;
}

void Camera::Update(float Dt)
{
    if(_Focus == nullptr)
    {
        return;
    }
    //TODO implement camera modes
    Vector2 Target = _Focus->Box.Center();
    switch(_CurrentMode)
    {
        case CameraMode::Fixed:
            _Position = Target;
            break;

        case CameraMode::Lazy:
            _Position+=Engine::Instance().GetRenderSize()*0.5f;
            UpdateLazy(Dt, Target);
            break;
        default:
            break;
    }
    _Position-=Engine::Instance().GetRenderSize()*0.5f;
    _Position.x = std::round(_Position.x);
    _Position.y = std::round(_Position.y);

    Engine::Instance().GetRenderer().SetViewPosition(_Position*-1);    
}

void Camera::UpdateLazy(float Dt, Vector2& Target)
{
    
}