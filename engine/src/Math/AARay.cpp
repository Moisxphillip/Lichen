#include "Math/AARay.hpp"
#include "Math/Physics.hpp"
#include "Core/Engine.hpp"

AARay::AARay(GameObject& GameObjAssoc, Vector2 Origin, Vector2 Direction)
: AACollider(GameObjAssoc, AAFormat::Circle, ColliderKind::Trigger)
{
    _Ray.Origin = Origin;
    _Ray.Direction = Direction;
}

void AARay::SetRay(Ray R)
{
    _Ray = R;
}

Ray& AARay::GetRay()
{
    return _Ray;
}


void AARay::PhysicsUpdate(float Dt)
{
    _Ray.Origin = Parent.Box.Center() + Offset.Rotate(Parent.Angle);
}

void AARay::Render()
{
#ifdef DEBUG 
	_Form.DrawLine(_Ray.Origin, _Ray.Direction, Color("#00ffff"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView());
#endif//_DEBUG
}