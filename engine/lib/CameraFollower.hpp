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
        bool Is(std::string);
};


#endif//LICHEN_CAMFOLLOW