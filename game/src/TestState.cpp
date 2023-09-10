#include "../lib/TestState.hpp"
#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Text.hpp"
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


Sprite* sprite = nullptr;
Text* text = nullptr;
bool shading = false;
Draw *draw = nullptr;
void Test01::LoadAssets()
{
    draw = new Draw();

    GameObject* imgo = new GameObject();
    sprite = new Sprite(*imgo, "./res/img/elf2.png");
    // sprite->SetScale(Vector2(0.5,0.5));
    imgo->Box.Redimension(Vector2(sprite->GetWidth(), sprite->GetHeight()));
    imgo->Box.SetCenter(Vector2(640,360));
    imgo->AddComponent(sprite);
    AddGameObj(imgo);

    imgo = new GameObject();
    imgo->Depth = DepthMode::Foreground;
    text = new Text(*imgo, "./res/ttf/Caviar.ttf", 20, TextStyle::BLENDED, ".", Color("#ffffff"));
    imgo->Box.x = 0;
    imgo->Box.y = 0;
    imgo->AddComponent(text);
    AddGameObj(imgo);
    
}

Timer alter;
void Test01::PhysicsUpdate(float Dt)
{
    Input& input = Input::Instance();
    //Rectangle
    // A.x = input.MousePosition().x - 40;
    // A.y = input.MousePosition().y - 40;
    
    //Circle
    // A.x = input.MousePosition().x;
    // A.y = input.MousePosition().y;

    if(input.KeyJustPressed(Key::S))
    {
        Shader& sh = sprite->GetShader();

        if(!shading)
        {
            sh.SubstituteShader("./engine/shader/Extra.vert","./engine/shader/Extra.frag");
            shading = true;
            // sprite->GetShader().SetUniform1i("U_PixelSize", 4);
        }
        else
        {
            sh.SubstituteShader();
            shading = false;
            alter.Restart();
        }
    }
}

void Test01::Update(float Dt)
{
    
    if(shading && sprite)
    {
        // alter.Update(Dt);
        // sprite->GetShader().SetUniform1f("U_Time", alter.Get());
    }
    // AABB::CheckAndResolve(A,B);
    // AABB::CheckAndResolve(A,C);
    // AABB::CheckAndResolve(D,A);
    // AABB::CheckAndResolve(A,E);
    // AABB::CheckAndResolve(D,B);
    // AABB::CheckAndResolve(B,E);
    // AABB::CheckAndResolve(C,D);
    // AABB::CheckAndResolve(C,E);
    // AABB::CheckAndResolve(D,E);
    if(Input::Instance().KeyJustPressed(Key::O))
	{
		Window& X = Engine::Instance().GetWindow();
		glm::mat4 Proj =  glm::ortho(0.0f, (float)X.GetWidth(), (float)X.GetHeight(), 0.0f, -1000.0f, 1000.0f);
		X.SetProjection(Proj);
	}
	if(Input::Instance().KeyJustPressed(Key::P))
	{
		Window& X = Engine::Instance().GetWindow();
		glm::mat4 Proj =  glm::perspective(glm::radians(45.0f), (float)X.GetWidth()/(float)X.GetHeight(), -1000.0f, 1000.0f);
		X.SetProjection(Proj);

	}
    if(text)
    {
        text->SetText(std::to_string(1.0f/Dt) + " Fps");
    }


    if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        delete draw;
        draw = nullptr;
        sprite = nullptr;
        text = nullptr;
    }
}



void Test01::Render()
{
    Window& window = Engine::Instance().GetWindow();
    Renderer& renderer = Engine::Instance().GetRenderer();

    if(draw && shading)
    {
        draw->DrawRectangle(Rect(A.x, A.y, A.w, A.h), Color("#00ff00"), window.GetProjection(), renderer.GetView());
        // // draw->DrawCircle(Circle(A.x, A.y, A.r), Color("#00ff00"), window.GetProjection(), renderer.GetView());
        // draw->DrawCircle(Circle(B.x, B.y, B.r), Color("#ff0000"), window.GetProjection(), renderer.GetView());
        // draw->DrawCircle(Circle(E.x, E.y, E.r), Color("#00f0f0"), window.GetProjection(), renderer.GetView());
        // draw->DrawRectangle(Rect(C.x, C.y, C.w, C.h), Color("#0000ff"), window.GetProjection(), renderer.GetView());
        // draw->DrawRectangle(Rect(D.x, D.y, D.w, D.h), Color("#f0f000"), window.GetProjection(), renderer.GetView());
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
