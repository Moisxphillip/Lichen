#ifndef LICHEN_AABB
#define LICHEN_AABB

#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Vector2.hpp"

enum class AAFormat
{
    Rectangle,
    Circle,
};

enum class ColliderKind
{
    Trigger,
    Rigid,
    Stationary,
};

class AACollider
{
    private:
        float _Mass, _Restitution, _InvMass;
    public:
        AACollider(AAFormat Format, ColliderKind Property, float Mass=1.0f, float Restitution=0.1f);
        
        Rectangle Rectan;//please use just one
        Circle Circ;
        
        AAFormat Format;
        ColliderKind Property;
        Vector2 Position;
        Vector2 Velocity;
        Vector2 Force;
        void SetMass(float Mass);
        void SetRestitution(float Restitution);
        void SetVelocity(Vector2 Velocity);
        float GetMass();
        float GetInvMass();
        float GetRestitution();
        void ApplyForce(Vector2 Force);
};

class Physics
{
    private:
        struct Manifold
        {
            float Penetration;
            Vector2 Normal;
        };
        static float _CorrectionPercent;
        static float _CorrectionSlop;

        static bool _Intersects(Rectangle& A, Rectangle& B);
        static bool _Intersects(Rectangle& A, Circle& B);
        static bool _Intersects(Circle& A, Circle& B);

        static void _CollisionData(AACollider& A, AACollider& B, Manifold& M);
        static void _RectData(Rectangle& A, Rectangle& B, Manifold& M);
        static void _CircData(Circle& A, Circle& B, Manifold& M);
        static void _RectCircData(Rectangle& A, Circle& B, Manifold& M);
        static void _LinearProjection(AACollider& A, AACollider& B, Manifold& M);
        
    public:

        static bool CheckCollision(AACollider& A, AACollider& B);
        static void ResolveCollision(AACollider& A, AACollider& B);
        static void Integrate(AACollider& A, float Dt);
};

#endif//LICHEN_AABBCOLLISION