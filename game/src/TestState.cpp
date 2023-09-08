#include "../lib/TestState.hpp"
#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/AABB.hpp"
#include "../../engine/lib/Draw.hpp"

Test01::Test01()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
}

Test01::~Test01()
{
}

TestRect A = {0,0,80,80, true, false, 100};
// TestCircle A = {0,0,50,     true, false, 100};
TestCircle B = {980,360,80, false, true, 100}; //Statico
TestCircle E = {720,200,50,     true, false, 100};
TestRect C = {250-75,360-65,150,130, false, true, 100};//Statico
TestRect D = {500,300,80,80, true, false, 100};


Draw *draw = nullptr;
void Test01::LoadAssets()
{
    draw = new Draw();
}


void Test01::PhysicsUpdate(float Dt)
{
    Input& input = Input::Instance();
    //Rectangle
    A.x = input.MousePosition().x - 40;
    A.y = input.MousePosition().y - 40;
    
    //Circle
    // A.x = input.MousePosition().x;
    // A.y = input.MousePosition().y;

    if((input.KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        delete draw;
        draw=nullptr;
    }
}

void Test01::Update(float Dt)
{
    
    AABB::CheckAndResolve(A,B);
    AABB::CheckAndResolve(A,C);
    AABB::CheckAndResolve(D,A);
    AABB::CheckAndResolve(A,E);
    AABB::CheckAndResolve(D,B);
    AABB::CheckAndResolve(B,E);
    AABB::CheckAndResolve(C,D);
    AABB::CheckAndResolve(C,E);
    AABB::CheckAndResolve(D,E);

}



void Test01::Render()
{
    Window& window = Engine::Instance().GetWindow();
    Renderer& renderer = Engine::Instance().GetRenderer();

    if(draw)
    {
        draw->DrawRectangle(Rect(A.x, A.y, A.w, A.h), Color("#00ff00"), window.GetProjection(), renderer.GetView());
        // draw->DrawCircle(Circle(A.x, A.y, A.r), Color("#00ff00"), window.GetProjection(), renderer.GetView());
        draw->DrawCircle(Circle(B.x, B.y, B.r), Color("#ff0000"), window.GetProjection(), renderer.GetView());
        draw->DrawCircle(Circle(E.x, E.y, E.r), Color("#00f0f0"), window.GetProjection(), renderer.GetView());
        draw->DrawRectangle(Rect(C.x, C.y, C.w, C.h), Color("#0000ff"), window.GetProjection(), renderer.GetView());
        draw->DrawRectangle(Rect(D.x, D.y, D.w, D.h), Color("#f0f000"), window.GetProjection(), renderer.GetView());
    }
}


void Test01::Start()
{
    LoadAssets();
}

void Test01::Pause()
{

}

void Test01::Resume()
{

}
