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
    Vector2 Rot = Offset.Rotate(Parent.Angle);
    Position = Parent.Box.Center() + Rot;
    Physics::Integrate(*this, Dt);
    _Ball.SetCenter(Position);
    Parent.Box.SetCenter(Position - Rot);
}

void AACircle::Render()
{
#ifdef DEBUG 
    // Vector2 Rot = Offset.Rotate(Parent.Angle);//TODO Fix this after implementing overloaded operations for circles
	_Form.DrawCircle(_Ball, Color("#00ffff"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView());
#endif//_DEBUG
}