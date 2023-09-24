#include "Components/Collider.hpp"
#include "Core/Engine.hpp"

Collider::Collider(GameObject& GameObj, Vector2 Scale, Vector2 Offset)
: Component(GameObj)
{
    _Scale = Scale;
    _Offset = Offset;
	_Type = ComponentType::Collider;
}

Collider::Collider(GameObject& GameObj)
: Collider(GameObj, Vector2(1,1), Vector2(0,0))
{
}

void Collider::SetScale(Vector2 NewScale)
{
    _Scale = NewScale;
}
void Collider::SetOffset(Vector2 NewOffset)
{
    _Offset = NewOffset;
}

void Collider::Render() 
{
#ifdef DEBUG 
	_Form.DrawRectangle(Box, Color("#ff0000"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView(),
		Parent.Angle);
#endif //_DEBUG
}

void Collider::LateUpdate(float Dt)
{
    Box = Parent.Box*_Scale;
	Vector2 Rot = _Offset;
	Rot.Rotate(Parent.Angle);
	Box.SetCenter(Parent.Box.Center()+Rot);
}