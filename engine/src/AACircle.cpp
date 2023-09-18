#include "../lib/AACircle.hpp"
#include "../lib/Physics.hpp"
#include "../lib/Engine.hpp"

AACircle::AACircle(GameObject& GameObjAssoc, ColliderKind Property, Circle Ball, float Mass, float Restitution)
: AACollider(GameObjAssoc, AAFormat::Circle, Property, Mass, Restitution)
{
    this->_Ball = Ball;
}

Circle& AACircle::GetBall()
{
    return _Ball;
}

void AACircle::SetBall(Circle B)
{
    _Ball = B;
}

void AACircle::PhysicsUpdate(float Dt)
{
    Position = Parent.Box.Center() + Offset.Rotate(Parent.Angle);
    Physics::Integrate(*this, Dt);
    _Ball.SetCenter(Position);
    Parent.Box.SetCenter(Position - Offset.Rotate(Parent.Angle));
}

void AACircle::Render()
{
#ifdef DEBUG 
	_Form.DrawCircle(_Ball, Color("#00ff00"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView());
#endif//_DEBUG
}