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
        void SetMaxSpeed(float);
        void SetMode(float);

        static Vector2 Center();
        static Vector2 Position();
        void Follow(GameObject*);
        bool IsFollowing();
        void Unfollow();
        void SetCameraMode(CameraMode);
        void SetCameraFormat(CameraFormat);
        void SetRectangleBounds(Rectangle);
        void SetCircleBounds(Circle);
        void Update(float);
        void UpdateLazy(float, Vector2&);

};

#endif//LICHEN_CAMERA
