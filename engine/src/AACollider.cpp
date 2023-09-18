#include "../lib/AACollider.hpp"
#include "../lib/Physics.hpp"

#include <algorithm>
#include <cmath>

Ray AACollider::_L{Vector2(0.0f,0.0f),Vector2(0.0f,0.0f)};
Circle AACollider::_C(0.0f,0.0f,0.0f);
Rectangle AACollider::_R(0.0f,0.0f,0.0f,0.0f);

AACollider::AACollider(GameObject& GameObjAssoc, AAFormat Format, ColliderKind Property, float Mass, float Restitution)
: Component(GameObjAssoc), Offset(0.0f, 0.0f), Force(0.0f, 0.0f)
{
    _Type = ComponentType::AACollider;
    this->Format = Format;
    this->Property = Property;
    SetMass(Mass);
    _Friction = 0.01f;
    _Restitution = Restitution;
}

void AACollider::SetFriction(float Friction)
{
    _Friction = std::clamp(Friction, 0.0f, 1.0f);
}

void AACollider::SetMass(float Mass)
{
    _InvMass = (Property == ColliderKind::Stationary || Mass == 0) ? 0 : 1.0f/Mass;
}

void AACollider::SetRestitution(float Restitution)
{
    _Restitution = Restitution;
}

float AACollider::GetFriction()
{
    return _Friction;
}

float AACollider::GetMass()
{
    return (_InvMass == 0 ? 0 : 1.0f/_InvMass);
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

Circle& AACollider::GetBall()
{
    return _C;
}

Ray& AACollider::GetRay()
{
    return _L;
}

Rectangle& AACollider::GetRect()
{
    return _R;
}

void AACollider::SetBall(Circle B)
{    
}

void AACollider::SetRay(Ray R)
{
}

void AACollider::SetRect(Rectangle R)
{
}

//Inheritance
void AACollider::PhysicsUpdate(float Dt)
{
}

void AACollider::Update(float Dt)
{
}

void AACollider::Render()
{
}
