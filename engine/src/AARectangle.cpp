#include "../lib/AARectangle.hpp"
#include "../lib/Physics.hpp"
#include "../lib/Engine.hpp"

AARectangle::AARectangle(GameObject& GameObjAssoc, ColliderKind Property, Rectangle Rect, float Mass, float Restitution)
: AACollider(GameObjAssoc, AAFormat::Rectangle, Property, Mass, Restitution)
{
    _Rect = Rect;
}

Rectangle& AARectangle::GetRect()
{
    return _Rect;
}

void AARectangle::SetRect(Rectangle R)
{
    _Rect = R;
}

void AARectangle::PhysicsUpdate(float Dt)
{
    Position = Parent.Box.Center() + Offset.Rotate(Parent.Angle);
    Physics::Integrate(*this, Dt);
    _Rect.SetCenter(Position);
    Parent.Box.SetCenter(Position - Offset.Rotate(Parent.Angle));
}

void AARectangle::Render()
{
#ifdef DEBUG 
	_Form.DrawRectangle(_Rect, Color("#ff0000"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView(),
		Parent.Angle);
#endif //_DEBUG
}