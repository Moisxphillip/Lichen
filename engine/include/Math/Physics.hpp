#ifndef LICHEN_PHYSICS
#define LICHEN_PHYSICS

#include "Math/Rectangle.hpp"
#include "Math/Circle.hpp"
#include "Math/Vector2.hpp"
#include "Components/AACollider.hpp"
#include "Components/AARay.hpp"


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
        static bool _Intersects(Rectangle& A, Ray& B);
        static bool _Intersects(Circle& A, Circle& B);
        static bool _Intersects(Circle& A, Ray& B);
        // static bool _Intersects(Ray& A, Ray& B);//Won't be needed for now


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

#endif//LICHEN_PHYSICS