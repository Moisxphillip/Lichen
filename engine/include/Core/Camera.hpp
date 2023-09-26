#ifndef LICHEN_CAMERA
#define LICHEN_CAMERA

#include "Math/Vector2.hpp"
#include "Math/Circle.hpp"
#include "Core/GameObject.hpp"

enum class CameraMode
{
    Fixed,
    Lazy,
    Ahead,
    Pointer,
};

enum class CameraFormat
{
    Rectangle,
    Circle,
};

class Camera
{
    private:
        GameObject* _Focus;
        static Vector2 _Position;
        Vector2 _Velocity;
        float _MaxSpeed;
        float _Acceleration;
        CameraMode _CurrentMode;
        CameraFormat _CurrentForm;

        Rectangle _RectBounds;
        Circle _CircBounds;

    public:
        
        Camera();

        static Vector2 Center();
        static Vector2 Position();
        void Follow(GameObject* Focus);
        bool IsFollowing();
        void Unfollow();
        void SetCameraMode(CameraMode Mode);
        void SetCameraFormat(CameraFormat Format);
        void SetRectangleBounds(Rectangle Bounds);
        void SetCircleBounds(Circle Bounds);
        void Update(float Dt);
        void UpdateLazy(float Dt, Vector2& Position);

};

#endif//LICHEN_CAMERA
