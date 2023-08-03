#include "../lib/Collider.hpp"
#include "../lib/Game.hpp"
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
	Update(0);
	Vector2 Center = Box.Center();
	SDL_Point SDLPoints[5];

	Vector2 Point = (Vector2(Box.x, Box.y) - Center).Rotate(GameObjAssoc.Angle)
					+ Center - Game::Instance().GetState().Cam.Position;
	SDLPoints[0] = {(int)Point.x, (int)Point.y};
	SDLPoints[4] = {(int)Point.x, (int)Point.y};
	
	Point = (Vector2(Box.x + Box.w, Box.y) - Center).Rotate(GameObjAssoc.Angle)
					+ Center - Game::Instance().GetState().Cam.Position;
	SDLPoints[1] = {(int)Point.x, (int)Point.y};
	
	Point = (Vector2(Box.x + Box.w, Box.y + Box.h) - Center).Rotate(GameObjAssoc.Angle)
					+ Center - Game::Instance().GetState().Cam.Position;
	SDLPoints[2] = {(int)Point.x, (int)Point.y};
	
	Point = (Vector2(Box.x, Box.y + Box.h) - Center).Rotate(GameObjAssoc.Angle)
					+ Center - Game::Instance().GetState().Cam.Position;
	SDLPoints[3] = {(int)Point.x, (int)Point.y};

	SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::Instance().GetRenderer(), SDLPoints, 5);
#endif //_DEBUG
}

void Collider::Start()
{
    
}

void Collider::Update(float Dt)
{
    Box = GameObjAssoc.Box*_Scale;
	Vector2 Rot = _Offset;
	Rot.Rotate(GameObjAssoc.Angle);
	Box.SetCenter(GameObjAssoc.Box.Center()+Rot);
}