#include "../lib/TestState.hpp"
#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Text.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/Physics.hpp"
#include "../../engine/lib/Draw.hpp"
#include "../../engine/lib/Particles.hpp"

#include "../../engine/lib/AACircle.hpp"
#include "../../engine/lib/AARectangle.hpp"


Test01::Test01()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
}

Test01::~Test01()
{
}

Sprite* sprite = nullptr;
Text* text = nullptr;
bool shading = false;
Draw *draw = nullptr;

AARectangle* Aa = nullptr;


ParticleManager* Pm;
void Test01::LoadAssets()
{
    draw = new Draw();
    Pm = new ParticleManager;

    GameObject* ColObj = new GameObject();
    AACircle* circle = new AACircle(*ColObj, ColliderKind::Rigid, Circle(640,360, 50));
    ColObj->AddComponent(circle);
    ColObj->Box.SetCenter(Vector2(640,360));
    AddGameObj(ColObj);
    
    ColObj = new GameObject();
    AARectangle* rect = new AARectangle(*ColObj, ColliderKind::Rigid, Rectangle(100,100, 100, 50));
    Aa = rect;
    ColObj->AddComponent(rect);
    ColObj->Box.SetPosition(rect->GetRect().Position());
    AddGameObj(ColObj);

    

    // Aa.Ball.r = 40;
    // // Aa.Position = Aa.Ball.Center();//mouse pointer
 
    // Aa.Ball.SetCenter(Vector2(640,0));//Drop test
    // Aa.Position = Aa.Ball.Center();
    // Aa.SetVelocity(Vector2(0,6));
    // // Aa.SetRestitution(0.8);

    // Aa.Rect.Redimension(Vector2(80,80));
    // Ab.Rect.Redimension(Vector2(80,80));
    // Ab.Rect.SetCenter(Vector2(640, 360));
    // Ab.Position = (Vector2(640, 360));
    
    // Ab.Ball.r = 40;
    // Ab.Ball.SetCenter(Vector2(640, 360));
    // Ab.Position = Ab.Ball.Center();

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
    Aa->SetVelocity((input.MousePosition()-Aa->Position));

    if(input.MousePressedDown(MouseButton::Left))
    {
        Particle z;
        z.Size =  Vector2(0.3,0.3);
        z.Position =  input.MousePosition();
        z.Velocity =  Vector2(50,0);
        z.Acceleration =  Vector2(0,300);
        z.Angle = 0;
        z.Spread = 3.1415f;
        z.Duration = 3.0f;
        z.Windswept = true;
        z.ColorInterpolation = true;
        z.StartColor = Color("#002200ff");
        z.EndColor = Color("#00aa0000");
        Pm->Emit(z);
    }

    //TODO transfer to appropriate place, add the masks to it
	for(int i = 0; i< (int)StateGameObjects.size()-1; i++)
	{
		if(!StateGameObjects[i]->Contains(ComponentType::AACollider))
		{
			continue;
		}

		AACollider* ColA = (AACollider*)StateGameObjects[i]->GetComponent(ComponentType::AACollider);
		for(int j = i+1; j < (int)StateGameObjects.size(); j++)
		{

			if(!StateGameObjects[j]->Contains(ComponentType::AACollider) /*|| //Activate once object masks are being used
				(((StateGameObjects[i]->Represents & StateGameObjects[j]->Interacts) 
				| (StateGameObjects[j]->Represents & StateGameObjects[i]->Interacts)) 
				== CollisionMask::None)*/)
			{
				continue;
			}

			AACollider* ColB = (AACollider*)StateGameObjects[j]->GetComponent(ComponentType::AACollider);
			if((Physics::CheckCollision(*ColA, *ColB)))
			{
                Physics::ResolveCollision(*ColA, *ColB);
				StateGameObjects[i]->OnCollision(*StateGameObjects[j]);
				StateGameObjects[j]->OnCollision(*StateGameObjects[i]);
			}
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

    if(text && Engine::Instance().GetPing())
    {
        text->SetText(std::to_string(1.0f/Dt) + " Fps");
    }

    if(Input::Instance().KeyJustPressed(Key::S))
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
    Pm->Update(Dt);
    if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        delete draw;
        delete Pm;
        Pm = nullptr;
        draw = nullptr;
        sprite = nullptr;
        text = nullptr;
    }
}

void Test01::Render()
{
    Window& window = Engine::Instance().GetWindow();
    Renderer& renderer = Engine::Instance().GetRenderer();
    if(draw)
    {
        // draw->DrawRectangle(Aa.Rect, Color("#f0000f"), window.GetProjection(), renderer.GetView());
        // draw->DrawCircle(Ab.Ball, Color("#0f00f0"), window.GetProjection(), renderer.GetView());
        // draw->DrawCircle(Aa.Ball, Color("#f0000f"), window.GetProjection(), renderer.GetView());
        // draw->DrawRectangle(Ab.Rect, Color("#0f00f0"), window.GetProjection(), renderer.GetView());
    }

    if(draw && shading)
    {
        draw->DrawRectangle(Rectangle(0, 0, 10, 10), Color("#00ff00"), window.GetProjection(), renderer.GetView());
    }
    if(Pm)
    {
        Pm->Render();
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

    // if(Input::Instance().KeyJustPressed(Key::O))
	// {
	// 	Window& X = Engine::Instance().GetWindow();
	// 	glm::mat4 Proj =  glm::ortho(0.0f, (float)X.GetWidth(), (float)X.GetHeight(), 0.0f, -1000.0f, 1000.0f);
	// 	X.SetProjection(Proj);
	// }
	// if(Input::Instance().KeyJustPressed(Key::P))
	// {
	// 	Window& X = Engine::Instance().GetWindow();
	// 	glm::mat4 Proj =  glm::perspective(glm::radians(45.0f), (float)X.GetWidth()/(float)X.GetHeight(), -1000.0f, 1000.0f);
	// 	X.SetProjection(Proj);
	// }

//Optimized
// bool SortLayers(GameObject A, GameObject B)
// {
//     if(A.Depth < B.Depth)
//         return true;
//     if(A.Depth > B.Depth)
//         return false;
//     if (A.Depth == DepthMode::Dynamic)
//         return A.Box.y+A.Box.h < B.Box.y+B.Box.h;
//     return A.GetLayer() < B.GetLayer(); 
// }
    //Unoptimized:
    // if(A.Depth == DepthMode::Background)
    // {
    //     if(B.Depth == DepthMode::Background)
    //         return A.GetLayer() < B.GetLayer();
    //     return true;
    // } 
    // else if (A.Depth == DepthMode::Dynamic)
    // {
    //     if(B.Depth == DepthMode::Background)
    //         return false;
    //     if(B.Depth == DepthMode::Dynamic)
    //         return A.Box.y+A.Box.h < B.Box.y+B.Box.h;
    //     return true;
    // }
    // if(B.Depth == DepthMode::Foreground)
    //     return A.GetLayer() < B.GetLayer();
    // return false;
// TestRect A = {0,0,80,80, true, false, 100};
// // TestCircle A = {0,0,50,     true, false, 100};
// TestCircle B = {980,360,80, false, true, 100}; //Statico
// TestCircle E = {720,200,50,     true, false, 100};
// TestRect C = {250-75,360-65,150,130, false, true, 100};//Statico
// TestRect D = {500,300,80,80, true, false, 100};

    //rectangle
    // A.x = input.MousePosition().x - 40;
    // A.y = input.MousePosition().y - 40;
    //Circle
    // A.x = input.MousePosition().x;
    // A.y = input.MousePosition().y;
    // // draw->DrawCircle(Circle(A.x, A.y, A.r), Color("#00ff00"), window.GetProjection(), renderer.GetView());
    // draw->DrawCircle(Circle(B.x, B.y, B.r), Color("#ff0000"), window.GetProjection(), renderer.GetView());
    // draw->DrawCircle(Circle(E.x, E.y, E.r), Color("#00f0f0"), window.GetProjection(), renderer.GetView());
    // draw->DrawRectangle(Rectangle(C.x, C.y, C.w, C.h), Color("#0000ff"), window.GetProjection(), renderer.GetView());
    // draw->DrawRectangle(Rectangle(D.x, D.y, D.w, D.h), Color("#f0f000"), window.GetProjection(), renderer.GetView());