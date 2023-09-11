#include "../lib/AABB.hpp"

#include <algorithm>
#include <cmath>

AACollider::AACollider(AAFormat Format, ColliderKind Property, float Mass, float Restitution)
{
    this->Format = Format;
    this->Property = Property;
    SetMass(Mass);
    _Restitution = Restitution;
    Force = Vector2(0.0f, 0.0f);
}
void AACollider::SetMass(float Mass)
{
    _Mass = Mass;
    _InvMass = (Property == ColliderKind::Stationary || Mass == 0) ? 0 : 1.0f/Mass;
}

void AACollider::SetRestitution(float Restitution)
{
    _Restitution = Restitution;
}

float AACollider::GetMass()
{
    return _Mass;
}

float AACollider::GetInvMass()
{
    return _InvMass;
}

float AACollider::GetRestitution()
{
    return _Restitution;
}

void AACollider::ApplyForce(Vector2 Force)
{
    this->Force+=Force;
}

void AACollider::SetVelocity(Vector2 Velocity)
{
    this->Velocity=Velocity;
}

//Collision check
float Physics::_CorrectionPercent = 0.2f; // should be between 20%-80% 
float Physics::_CorrectionSlop = 0.01f; // should be around 0.01-0.1 

bool Physics::CheckCollision(AACollider& A, AACollider& B)
{
    if(A.Format == AAFormat::Rectangle)
    {
        if(B.Format == AAFormat::Rectangle)
        {
            return _Intersects(A.Rectan, B.Rectan);
        } 
        return _Intersects(A.Rectan, B.Circ);
    }

    if(B.Format == AAFormat::Rectangle)
    {
        return _Intersects(B.Rectan, A.Circ);
    }
    return _Intersects(A.Circ, B.Circ);
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

bool Physics::_Intersects(Circle& A, Circle& B)
{
    return (std::pow(A.x-B.x, 2) + std::pow(A.y-B.y, 2)) < std::pow(A.r+B.r, 2);
}

//Collision resolution
void Physics::ResolveCollision(AACollider& A, AACollider& B)
{
    if(A.Property == ColliderKind::Trigger || B.Property == ColliderKind::Trigger
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
    //Correction for accumulative floating point errors and sinking objects
    Vector2 Correction = M.Normal * (std::max(M.Penetration - _CorrectionSlop, 0.0f)/(A.GetInvMass() + B.GetInvMass()) * _CorrectionPercent);
    A.Position -= Correction * A.GetInvMass();
    B.Position += Correction * B.GetInvMass();
}

void Physics::_CollisionData(AACollider& A, AACollider& B, Manifold& M)
{
    if(A.Format == AAFormat::Rectangle)
    {
        if(B.Format == AAFormat::Rectangle)
        {
            _RectData(B.Rectan, A.Rectan, M);
            return;
        } 
        _RectCircData(A.Rectan, B.Circ, M);
        // M.Normal *= -1.0f; //Fixes normal direction since parameters invert here
        return;
    }
    if(B.Format == AAFormat::Rectangle)
    {
        _RectCircData(B.Rectan, A.Circ, M);
        M.Normal *= -1.0f; //Fixes normal direction since parameters invert here
        return ;
    }
    _CircData(A.Circ, B.Circ, M);
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
#include <iostream>
void Physics::_RectCircData(Rectangle& A, Circle& B, Manifold& M)
{
    Vector2 RelativeDist = B.Center() - A.Center();
    Vector2 Closest(std::max(A.x, std::min(B.x, A.x + A.w)), std::max(A.y, std::min(B.y, A.y + A.h))); 

    bool Inserted = RelativeDist == Closest;
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
    float Dist = (RelativeDist-Closest).Magnitude();
    M.Penetration = B.r - Dist;
}

void Physics::Integrate(AACollider& A, float Dt)
{
    Vector2 Acceleration = A.Force * A.GetInvMass() * Dt;
    A.Velocity+= Acceleration * Dt; 
    A.Position+= (A.Velocity)+(Acceleration * 0.5f * std::pow(Dt, 2));
}


// // Explicit Euler
// A.Position += A.Velocity * Dt;
// A.Velocity += A.Force * A.GetInvMass() * Dt;

// // Symplectic Euler 
// Vector2 Acceleration = A.Force * A.GetInvMass() * Dt;
// A.Position += A.Velocity * Dt;
