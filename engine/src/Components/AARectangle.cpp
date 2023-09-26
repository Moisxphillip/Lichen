#include "Components/AARectangle.hpp"
#include "Math/Physics.hpp"
#include "Core/Engine.hpp"

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
    Physics::Integrate(*this, Dt);
    _Rect.SetCenter(Position);
    Parent.Box.SetCenter(Position - Offset);
}

void AARectangle::Render()
{
#ifdef DEBUG 
    Vector2 Rot = Offset.Rotate(Parent.Angle);
	_Form.DrawRectangle(_Rect+Rot, Color("#ff00ff"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView(),
		Parent.Angle);
#endif //_DEBUG
}