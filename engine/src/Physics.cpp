#include "../lib/Physics.hpp"
#include "../lib/AARectangle.hpp"
#include "../lib/AACircle.hpp"

#include <algorithm>
#include <cmath>

//Collision check
float Physics::_CorrectionPercent = 0.2f; // should be between 20%-80% 
float Physics::_CorrectionSlop = 0.01f; // should be around 0.01-0.1 

bool Physics::CheckCollision(AACollider& A, AACollider& B)
{
    if(A.Format == AAFormat::Rectangle)
    {
        if(B.Format == AAFormat::Rectangle)
        {
            return _Intersects(A.GetRect(), B.GetRect());
        }
        else if(B.Format == AAFormat::Circle)
        {
            return _Intersects(A.GetRect(), B.GetBall());
        }
        return _Intersects(A.GetRect(), B.GetRay());
    }
    else if(A.Format== AAFormat::Ray)
    {
        if(B.Format == AAFormat::Rectangle)
        {
            return _Intersects(B.GetRect(), A.GetRay());
        }
        else if(B.Format == AAFormat::Circle)
        {
            return _Intersects(B.GetBall(), A.GetRay());
        }
        return false;//maybe implement ray collision tho?
    }

    if(B.Format == AAFormat::Rectangle)
    {
        return _Intersects(B.GetRect(), A.GetBall());
    }
    else if(B.Format == AAFormat::Ray)
    {
        return _Intersects(A.GetBall(), B.GetRay());
    }
    return _Intersects(A.GetBall(), B.GetBall());
}

bool Physics::_Intersects(Rectangle& A, Rectangle& B)
{
    if(A.x+A.h < B.x || A.x > B.x+B.h || A.y+A.h < B.y || A.y > B.y+B.h)
    {
        return false;
    }
    return true;
}

bool Physics::_Intersects(Rectangle& A, Circle& B)
{
    float ClosestX = std::max(A.x, std::min(B.x, A.x + A.w));
    float ClosestY = std::max(A.y, std::min(B.y, A.y + A.h));
    return std::pow(B.x - ClosestX, 2) + std::pow(B.y - ClosestY, 2) < std::pow(B.r, 2);
}

bool Physics::_Intersects(Rectangle& A, Ray& B)
{
    float X1 = (A.x - B.Origin.x) / B.Direction.x;
    float X2 = (A.x + A.w - B.Origin.x) / B.Direction.x;
    float Y1 = (A.y - B.Origin.y) / B.Direction.y;
    float Y2 = (A.y + A.h - B.Origin.y) / B.Direction.y;
    float Min = std::max(std::min(X1, X2), std::min(Y1, Y2));
    float Max = std::min(std::max(X1, X2), std::max(Y1, Y2));
    if (Max < 0 || Min > Max) 
    {
        return false;//no intersection
    }
    return true;//intersection occurred
}

bool Physics::_Intersects(Circle& A, Circle& B)
{
    return (std::pow(A.x-B.x, 2) + std::pow(A.y-B.y, 2)) < std::pow(A.r+B.r, 2);
}

bool Physics::_Intersects(Circle& A, Ray& B)
{
    Vector2 RayToCenter = A.Center() - B.Origin;
    float DotProduct = RayToCenter.Dot(B.Direction);
    float Discriminant = DotProduct * DotProduct - RayToCenter.Dot(RayToCenter) + A.r * A.r;
    if (Discriminant < 0) 
    {
        return false;
    }    
    float T1 = -DotProduct - std::sqrt(Discriminant);//intersection parameters
    float T2 = -DotProduct + std::sqrt(Discriminant);
    if (T1 < 0 && T2 < 0) 
    {
        return false;//no intersection
    }
    return true;
}

// bool Physics::_Intersects(Ray& A, Ray& B)//Won't be needed for now
// {
// }

//Collision resolution
void Physics::ResolveCollision(AACollider& A, AACollider& B)
{
    if(A.Property == ColliderKind::Trigger || B.Property == ColliderKind::Trigger
        || A.Format == AAFormat::Ray || B.Format == AAFormat::Ray
        || (A.Property == B.Property && A.Property == ColliderKind::Stationary))
    {
        return; //No resolution for triggers or stationaries together
    }

    Manifold M = {0.0f,Vector2(0.0f,0.0f)};
    _CollisionData(A, B, M);//Must be called when there's already knowledge of the collision
    Vector2 RelVelocity = B.Velocity-A.Velocity; //Relative Velocity of A and B

    float VelAlongNormal = RelVelocity.Dot(M.Normal);
    if(VelAlongNormal > 0) //Optimization for when things are moving apart
    {
        return;
    }
    float e = std::min(A.GetRestitution(), B.GetRestitution()); //Restitutes for the smaller restitution in the interaction
    float j = -(1.0f + e) * VelAlongNormal;// Impulse scalar (j)
    j /= (A.GetInvMass() + B.GetInvMass());
    
    //Calculate Impulse and apply to the velocities
    Vector2 Impulse = M.Normal*j;
    A.Velocity -= Impulse * (A.GetInvMass());
    B.Velocity += Impulse * (B.GetInvMass());
    _LinearProjection(A, B, M); //Fixes small errors and sinking if needed
}

void Physics::_LinearProjection(AACollider& A, AACollider& B, Manifold& M)
{
    Vector2 Correction = M.Normal * (std::max(M.Penetration - _CorrectionSlop, 0.0f)
        /(A.GetInvMass() + B.GetInvMass()) * _CorrectionPercent);
    A.Position -= Correction * A.GetInvMass();
    B.Position += Correction * B.GetInvMass();
}

void Physics::_CollisionData(AACollider& A, AACollider& B, Manifold& M)
{
    if(A.Format == AAFormat::Rectangle)
    {
        if(B.Format == AAFormat::Rectangle)
        {
            _RectData(B.GetRect(), A.GetRect(), M);
            return;
        } 
        _RectCircData(A.GetRect(), B.GetBall(), M);
        return;
    }
    if(B.Format == AAFormat::Rectangle)
    {
        _RectCircData(B.GetRect(), A.GetBall(), M);
        M.Normal *= -1.0f; //Fixes normal direction since parameters invert here
        return ;
    }
    _CircData(A.GetBall(), B.GetBall(), M);
}

void Physics::_RectData(Rectangle& A, Rectangle& B, Manifold& M)
{
    float XOverlap = std::min(A.x + A.w, B.x + B.w) - std::max(A.x, B.x);
    float YOverlap = std::min(A.y + A.h, B.y + B.h) - std::max(A.y, B.y);
    if(XOverlap < YOverlap) // Gets the normal of the colliding face based in the smaller overlap
    {
        (A.x < B.x ? M.Normal.x = -1.0f : M.Normal.x = 1.0f);
        M.Penetration = XOverlap;
        return;
    }    
    (A.y < B.y ? M.Normal.y = -1.0f : M.Normal.y = 1.0f);
    M.Penetration = YOverlap;
}

void Physics::_CircData(Circle& A, Circle& B, Manifold& M)
{
    Vector2 RelativeDist = B.Center() - A.Center();
    float RadiusSum = A.r+B.r;
    float Dist = RelativeDist.Magnitude();
    if(Dist != 0.0f)
    {
        M.Penetration = RadiusSum-Dist;
        M.Normal = Vector2(RelativeDist.x/Dist, RelativeDist.y/Dist);
        return;
    }
    M.Penetration = A.r; //Fixes rare cases where they occupy the same point in space
    M.Normal = Vector2(1.0f, 0.0f);
}

void Physics::_RectCircData(Rectangle& A, Circle& B, Manifold& M)
{
    Vector2 RelativeDist = B.Center() - A.Center();
    Vector2 Closest(std::max(A.x, std::min(B.x, A.x + A.w)), std::max(A.y, std::min(B.y, A.y + A.h))); 

    bool Inserted = A.Contains(B.Center());
    if (Inserted)
    {
        if(std::abs(RelativeDist.x) > std::abs(RelativeDist.y))
        {
            // Closest.x = (Closest.x > 0 ? A.x+A.w : A.x);
            Closest.x = (RelativeDist.x > 0 ? A.x+A.w : A.x);
        }
        else
        {
            // Closest.y = (Closest.y > 0 ? A.y+A.h : A.y);
            Closest.y = (RelativeDist.y > 0 ? A.y+A.h : A.y);
        }
    }

    //if center is inserted in the other form, must be repelled outwards
    M.Normal = (Inserted ? RelativeDist*-1.0f : RelativeDist).Normalized();    
    float Dist = (B.Center()-Closest).Magnitude();
    M.Penetration = B.r - Dist;
}

void Physics::Integrate(AACollider& A, float Dt)
{
    if(A.Property == ColliderKind::Stationary)
    {
        return;
    }
    Vector2 Acceleration = A.Force * A.GetInvMass() * Dt;
    A.Velocity+= Acceleration * Dt; 
    A.Velocity+=(A.Velocity * -A.GetFriction());
    A.Position+=(A.Velocity)+(Acceleration * 0.5f * std::pow(Dt, 2));
    A.Force = Vector2(0.0f,0.0f);
}

// // Explicit Euler
// A.Position += A.Velocity * Dt;
// A.Velocity += A.Force * A.GetInvMass() * Dt;

// // Symplectic Euler 
// Vector2 Acceleration = A.Force * A.GetInvMass() * Dt;
// A.Position += A.Velocity * Dt;