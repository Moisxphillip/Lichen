#ifndef LICHEN_CAMERA
#define LICHEN_CAMERA

#include "Vector2.hpp"
#include "GameObject.hpp"

class Camera
{
    private:
        GameObject* _Focus;
        
    public:
        Vector2 Position;
        Vector2 Speed;
        
        Camera();
        Vector2 Center();
        void Follow(GameObject*);
        bool IsFollowing();
        void Unfollow();
        void Update(float);

};

#endif//LICHEN_CAMERA