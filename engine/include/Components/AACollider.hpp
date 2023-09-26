#ifndef LICHEN_AACOLLIDER
#define LICHEN_AACOLLIDER

#include "Math/Vector2.hpp"
#include "Math/Circle.hpp"
#include "Components/Component.hpp"
#include "Graphics/Draw.hpp"

enum class AAFormat
{
    Rectangle,
    Circle,
    Ray,
};

enum class ColliderKind
{
    Trigger,
    Rigid,
    Stationary,
};


struct Ray
{
    Vector2 Origin;
    Vector2 Direction;
};

class AACollider : public Component
{
    protected:
        float _Restitution, _InvMass, _Friction;
        Draw _Form;
        static Ray _L;
        static Circle _C;
        static Rectangle _R;

    public:
        AACollider(GameObject& GameObjAssoc, AAFormat Format, ColliderKind Property, float Mass=1.0f, float Restitution=0.1f);

        AAFormat Format;
        ColliderKind Property;
        Vector2 Position;
        Vector2 Velocity;
        Vector2 Force;
        Vector2 Offset;


        void SetFriction(float Friction);
        void SetMass(float Mass);
        void SetRestitution(float Restitution);
        void SetVelocity(Vector2 Velocity);
        float GetFriction();
        float GetMass();
        float GetInvMass();
        float GetRestitution();
        void ApplyForce(Vector2 Force);

        //Inheritance section
        virtual Circle& GetBall();
        virtual Ray& GetRay();
        virtual Rectangle& GetRect();
        virtual void SetBall(Circle B);
        virtual void SetRay(Ray R);
        virtual void SetRect(Rectangle R);

        virtual void Start();
        virtual void PhysicsUpdate(float Dt);
        virtual void Update(float Dt);
        virtual void Render();
};

#endif//LICHEN_AACOLLIDER
