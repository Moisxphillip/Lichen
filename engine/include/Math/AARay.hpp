#ifndef LICHEN_AARAY
#define LICHEN_AARAY

#include "Math/AACollider.hpp"

class AARay : public AACollider
{
    private:
        Ray _Ray;

    public:
        AARay(GameObject& GameObjAssoc, Vector2 Origin, Vector2 Direction);
        void SetOrigin(Vector2 O);
        void SetDirection(Vector2 D);
        void SetRay(Ray R);
        Ray& GetRay();
        void PhysicsUpdate(float Dt);
        void Render();
};

#endif//LICHEN_AARAY