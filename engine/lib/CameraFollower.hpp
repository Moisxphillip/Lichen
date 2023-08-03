#ifndef LICHEN_CAMFOLLOW
#define LICHEN_CAMFOLLOW

#include "Component.hpp"

class CameraFollower: public Component
{
    private:

    public:
        Vector2 Offset;
        CameraFollower(GameObject&);
        void Update(float);
        void Render();
        bool Is(std::string);
        void Start();

};


#endif//LICHEN_CAMFOLLOW