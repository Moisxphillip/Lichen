#include <algorithm>
#include "Core/Camera.hpp"
#include "Core/Engine.hpp"

Vector2 Camera::_Position = Vector2(0.0f,0.0f);
Rectangle Camera::Boundaries = Rectangle(0,0,2000,2000);
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

// Vector2 Offset(0.0f,0.0f);

void Camera::Update(float Dt)
{
    if(_Focus == nullptr)
    {
        return;
    }
    //TODO implement camera modes
    // _Position -= Offset;
    Vector2 Target = _Focus->Box.Center();
    Vector2 HalfScreenSize = Engine::Instance().GetRenderSize()*0.5f;

    switch(_CurrentMode)
    {
        case CameraMode::Fixed:
            _Position = Target;
            break;

        case CameraMode::Lazy:
            _Position+=HalfScreenSize;
            UpdateLazy(Dt, Target);
            break;

        case CameraMode::Ahead:
            _Position+=HalfScreenSize;
            UpdateAhead(Dt, Target);
            break;

        default:
            break;
    }
    _Position-=HalfScreenSize;
    if(Boundaries.w !=0)
    {
        _Position.x = std::min(std::max(Boundaries.x, _Position.x), Boundaries.w - HalfScreenSize.x*2);
        _Position.y = std::min(std::max(Boundaries.y, _Position.y), Boundaries.h - HalfScreenSize.y*2);
    }
    // _Position += Offset;

    _Position.x = std::round(_Position.x);
    _Position.y = std::round(_Position.y);

    Engine::Instance().GetRenderer().SetViewPosition(_Position*-1);    
}


// float delay, playerVelocity, smoothness;
void Camera::UpdateLazy(float Dt, Vector2& Target)
{
    // Vector2 targetPos = Target + delay * playerVelocity;
//   _Position += (targetPos - _Position) * Dt * smoothness;
}

// #include <iostream>
// Vector2 MaxOffset(64, 64);
// Vector2 Accumulator(0, 0);
//Works like crap :/ fix this later
void Camera::UpdateAhead(float Dt, Vector2& Target)
{
    // Vector2 Variation = Target - _Position;
    // Accumulator += Variation;

    // Accumulator.x = std::clamp(Accumulator.x, -MaxOffset.x, MaxOffset.x);
    // Accumulator.y = std::clamp(Accumulator.y, -MaxOffset.y, MaxOffset.y);

    // Offset = Accumulator - Variation;
    // // Offset.x = std::clamp(Accumulator.x, -MaxOffset.x, MaxOffset.x);
    // // Offset.y = std::clamp(Accumulator.y, -MaxOffset.y, MaxOffset.y);
    
    // _Position = Target;

    // Variation.Normalize();
    // std::cout << Variation << '\n';
    // return;
    // if(Variation.MagnitudeSquared() > 0.2f && Variation.MagnitudeSquared() < 21568.0f)
    // _Position = Target;
}