#include "TestScene.hpp"
#include "Dummy.hpp"
#include "Enemy/Slime.hpp"

#include "EnemyFactory.hpp"
#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"
#include "Components/Text.hpp"
#include "Graphics/Draw.hpp"
#include "Math/Physics.hpp"
#include "Components/AACircle.hpp"
#include "Components/AARectangle.hpp"
#include "Tools/Particles.hpp"



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
// AACircle* Aa = nullptr;

ParticleManager* Pm;
void Test01::LoadAssets()
{
    draw = new Draw();
    Pm = new ParticleManager;

    GameObject* ColObj = new GameObject();
    AARectangle* rect = new AARectangle(*ColObj, ColliderKind::Rigid, Rectangle(100,100, 100, 50));
    Aa = rect;
    ColObj->AddComponent(rect);
    ColObj->Box.SetPosition(rect->GetRect().Position());
    AddGameObj(ColObj);

    ColObj = new GameObject();
    AACircle* circle = new AACircle(*ColObj, ColliderKind::Rigid, Circle(800,360, 50));
    // Aa = circle;
    ColObj->AddComponent(circle);
    ColObj->Box.SetCenter(circle->GetBall().Center());
    AddGameObj(ColObj);

    ColObj = new GameObject();
    circle = new AACircle(*ColObj, ColliderKind::Rigid, Circle(800,500, 70));
    // Aa = circle;
    ColObj->AddComponent(circle);
    ColObj->Box.SetCenter(circle->GetBall().Center());
    AddGameObj(ColObj);

    ColObj = new GameObject();
    circle = new AACircle(*ColObj, ColliderKind::Rigid, Circle(200,360, 30));
    // Aa = circle;
    ColObj->AddComponent(circle);
    ColObj->Box.SetCenter(circle->GetBall().Center());
    AddGameObj(ColObj);
    
    ColObj = new GameObject();
    circle = new AACircle(*ColObj, ColliderKind::Rigid, Circle(400,600, 30));
    // Aa = circle;
    ColObj->AddComponent(circle);
    ColObj->Box.SetCenter(circle->GetBall().Center());
    AddGameObj(ColObj);

    // ColObj = new GameObject();
    // rect = new AARectangle(*ColObj, ColliderKind::Rigid, Rectangle(30,41, 20, 600));
    // ColObj->AddComponent(rect);
    // ColObj->Box = rect->GetRect();
    // AddGameObj(ColObj);

    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Rigid, Rectangle(640,360, 100, 50));
    ColObj->AddComponent(rect);
    ColObj->Box.SetPosition(rect->GetRect().Position());
    AddGameObj(ColObj);

    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Rigid, Rectangle(800,70, 90, 90));
    ColObj->AddComponent(rect);
    ColObj->Box.SetPosition(rect->GetRect().Position());
    AddGameObj(ColObj);

//Boundaries
    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Stationary, Rectangle(0,0, 1280, 20));
    ColObj->AddComponent(rect);
    ColObj->Box = rect->GetRect();
    AddGameObj(ColObj);

    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Stationary, Rectangle(0,21, 20, 679));
    ColObj->AddComponent(rect);
    ColObj->Box = rect->GetRect();
    AddGameObj(ColObj);
    
    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Stationary, Rectangle(0, 700, 1280, 19));
    ColObj->AddComponent(rect);
    ColObj->Box = rect->GetRect();
    AddGameObj(ColObj);

    ColObj = new GameObject();
    rect = new AARectangle(*ColObj, ColliderKind::Stationary, Rectangle(1260,21, 20, 679));
    ColObj->AddComponent(rect);
    ColObj->Box = rect->GetRect();
    AddGameObj(ColObj);
    
    Engine::Instance().GetRenderer().SetClearColor((std::string)"#4c0317");

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

    GameObject* dummyobj = new GameObject(2);
    Dummy* dummy = new Dummy(*dummyobj);
    dummyobj->Box.SetCenter(Vector2(640, 150));
    dummyobj->AddComponent(dummy);
    AddGameObj(dummyobj);
    
    GameObject* slimeObj = new GameObject(2);
    Slime* slime = new Slime(*slimeObj);
    slimeObj->Box.SetCenter(Vector2(640, 150));
    slimeObj->AddComponent(slime);
    AddGameObj(slimeObj);
    Cam.Follow(slimeObj);

    
    GameObject* enemyObj = new GameObject(2);
    enemyObj->AddComponent(EnemyFactory::CreateEnemy(*enemyObj, EnemyType::GRUB, Vector2(100, 100)));
    AddGameObj(enemyObj);

}

Timer alter;
void Test01::PhysicsUpdate(float Dt)
{
    Input& input = Input::Instance();
    // if(Aa)
    //     Aa->SetVelocity((input.MousePosition()-Aa->Position));

    if(input.MousePressedDown(MouseButton::Left))
    {
        Particle z;
        z.Size =  Vector2(0.3,0.3);
        z.Position =  input.MousePosition();
        z.Velocity =  Vector2(50,0);
        z.Acceleration =  Vector2(0,300);
        z.Angle = 0;
        z.Spread = 3.1415f/2.0f;
        z.Duration = 2.0f;
        z.Windswept = true;
        z.ColorInterpolation = true;
        z.StartColor = Color("#002200ff");
        z.EndColor = Color("#00aa0000");
        Pm->Emit(z);
    }

    //TODO transfer to appropriate place, add the masks to it
	for(int i = 0; i< (int)SceneGameObjects.size()-1; i++)
	{
		if(!SceneGameObjects[i]->Contains(ComponentType::AACollider))
		{
			continue;
		}

		AACollider* ColA = (AACollider*)SceneGameObjects[i]->GetComponent(ComponentType::AACollider);
		for(int j = i+1; j < (int)SceneGameObjects.size(); j++)
		{
			if(!SceneGameObjects[j]->Contains(ComponentType::AACollider)  
				 /*||(((SceneGameObjects[i]->Represents & SceneGameObjects[j]->Interacts) //Activate once object masks are being used
				| (SceneGameObjects[j]->Represents & SceneGameObjects[i]->Interacts)) == CollisionMask::None) */
                )
			{
				continue;
			}

			AACollider* ColB = (AACollider*)SceneGameObjects[j]->GetComponent(ComponentType::AACollider);
			if((Physics::CheckCollision(*ColA, *ColB)))
			{
                Physics::ResolveCollision(*ColA, *ColB);
				SceneGameObjects[i]->OnCollision(*SceneGameObjects[j]);
				SceneGameObjects[j]->OnCollision(*SceneGameObjects[i]);
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

    if(Input::Instance().KeyJustPressed(Key::F5))
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