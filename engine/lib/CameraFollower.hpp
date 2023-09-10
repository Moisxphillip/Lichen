#ifndef LICHEN_CAMFOLLOW
#define LICHEN_CAMFOLLOW

#include "Component.hpp"

class CameraFollower: public Component
{
    private:

    public:
        Vector2 Offset;
        CameraFollower(GameObject&);
        void LateUpdate(float);
};


#endif//LICHEN_CAMFOLLOW