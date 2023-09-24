#ifndef LICHEN_CAMFOLLOW
#define LICHEN_CAMFOLLOW

#include "Components/Component.hpp"

class CameraFollower: public Component
{
    private:

    public:
        Vector2 Offset;
        CameraFollower(GameObject& Parent);
        void LateUpdate(float Dt);
};


#endif//LICHEN_CAMFOLLOW