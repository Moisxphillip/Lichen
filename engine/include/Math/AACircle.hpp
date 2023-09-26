#ifndef LICHEN_AACIRCLE
#define LICHEN_AACIRCLE

#include "Math/AACollider.hpp"
#include "Math/Circle.hpp"

class AACircle: public AACollider
{
    private:
        Circle _Ball;
    public:
        AACircle(GameObject& GameObjAssoc, ColliderKind Property, Circle Ball, float Mass=1.0f, float Restitution=0.1f);
        Circle& GetBall();
        void SetBall(Circle B);
        void PhysicsUpdate(float Dt);
        void Render();

};

#endif//LICHEN_AACIRCLE
