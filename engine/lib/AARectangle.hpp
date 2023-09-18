#ifndef LICHEN_AARECTANGLE
#define LICHEN_AARECTANGLE

#include "AACollider.hpp"

class AARectangle: public AACollider
{
    private:
        Rectangle _Rect;

    public:
        AARectangle(GameObject& GameObjAssoc, ColliderKind Property, Rectangle Rect, float Mass=1.0f, float Restitution=0.1f);
        Rectangle& GetRect();
        void SetRect(Rectangle R);
        void PhysicsUpdate(float Dt);
        void Render();

};

#endif//LICHEN_AARECTANGLE
