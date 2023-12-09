#include "Tools/SimpleMovement.hpp"


SimpleMovement::SimpleMovement(GameObject& Parent, Vector2 Velocity)
: Component(Parent), _Velocity(Velocity)
{
}

void SimpleMovement::SetMovement(Vector2 Velocity)
{
    _Velocity = Velocity;
}

Vector2 SimpleMovement::GetMovement()
{
    return _Velocity;
}

void SimpleMovement::PhysicsUpdate(float Dt)
{
    Parent.Box+=_Velocity*Dt;
}