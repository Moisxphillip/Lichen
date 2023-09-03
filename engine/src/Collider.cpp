#include "../lib/Collider.hpp"
#include "../lib/Engine.hpp"
// #define DEBUG

Collider::Collider(GameObject& GameObj, Vector2 Scale, Vector2 Offset)
: Component(GameObj)
{
    _Scale = Scale;
    _Offset = Offset;
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

bool Collider::Is(std::string Type)
{
    return ("Collider" == Type);
}

void Collider::Render() 
{
#ifdef DEBUG 
	_Form.DrawRectangle(Box, Color("#ff0000"), 
		Engine::Instance().GetWindow().GetProjection(), 
		Engine::Instance().GetRenderer().GetView());
	 //Fix when a native method for drawing forms is implemented
	// Vector2 Center = Box.Center();
	// SDL_Point SDLPoints[5];

	// Vector2 Point = (Vector2(Box.x, Box.y) - Center).Rotate(Parent.Angle)
	// 				+ Center - Engine::Instance().CurrentState().Cam.Position;
	// SDLPoints[0] = {(int)Point.x, (int)Point.y};
	// SDLPoints[4] = {(int)Point.x, (int)Point.y};
	
	// Point = (Vector2(Box.x + Box.w, Box.y) - Center).Rotate(Parent.Angle)
	// 				+ Center - Engine::Instance().CurrentState().Cam.Position;
	// SDLPoints[1] = {(int)Point.x, (int)Point.y};
	
	// Point = (Vector2(Box.x + Box.w, Box.y + Box.h) - Center).Rotate(Parent.Angle)
	// 				+ Center - Engine::Instance().CurrentState().Cam.Position;
	// SDLPoints[2] = {(int)Point.x, (int)Point.y};
	
	// Point = (Vector2(Box.x, Box.y + Box.h) - Center).Rotate(Parent.Angle)
	// 				+ Center - Engine::Instance().CurrentState().Cam.Position;
	// SDLPoints[3] = {(int)Point.x, (int)Point.y};

	// SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderDrawLines(Engine::Instance().GetRenderer(), SDLPoints, 5);
#endif //_DEBUG
}

void Collider::LateUpdate(float Dt)
{
    Box = Parent.Box*_Scale;
	Vector2 Rot = _Offset;
	Rot.Rotate(Parent.Angle);
	Box.SetCenter(Parent.Box.Center()+Rot);
}