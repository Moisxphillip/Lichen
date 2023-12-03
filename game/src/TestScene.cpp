#include "TestScene.hpp"

#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Graphics/Draw.hpp"
#include "Math/Physics.hpp"
#include "Tools/Particles.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include "Components/AACircle.hpp"
#include "Components/AARectangle.hpp"
#include "Components/TileMap.hpp"
#include "Components/CameraFollower.hpp"
#include "Components/CameraFollower.hpp"
#include "Components/Fade.hpp"

#include "Enemy/Slime.hpp"
#include "EnemyFactory.hpp"
#include "Character/Player.hpp"
#include "Tools/LoopSprite.hpp"

std::vector<std::vector<int>>* Test01::CollisionMap = nullptr;

Test01::Test01()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
    
}

Test01::~Test01()
{
}

Text* text = nullptr;
Fade* _Fader = nullptr;

#include "Components/Sound.hpp"
void Test01::LoadAssets()
{
 
    Engine::Instance().GetRenderer().SetClearColor((std::string)"#4c0317");

    GameObject* imgo = new GameObject();
    imgo->Depth = DepthMode::Foreground;
    text = new Text(*imgo, "./res/ttf/Caviar.ttf", 20, TextStyle::BLENDED, ".", Color("#ffffff"));
    imgo->Box.x = 0;
    imgo->Box.y = 0;
    imgo->AddComponent(text);
    imgo->AddComponent(new CameraFollower(*imgo));
    AddGameObj(imgo);

    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->Box.SetCenter(Vector2(640, 750));
    playerObj->AddComponent(player);
    AddGameObj(playerObj);
    
    GameObject* enemyObj = new GameObject(2);
    enemyObj->AddComponent(EnemyFactory::CreateEnemy(*enemyObj, EnemyType::GRUB, Vector2(100, 100)));
    AddGameObj(enemyObj);

    //Testing map
    GameObject* Tiles = new GameObject(-5);
    Tiles->Depth = DepthMode::Background;
    TileSet* Tset = new TileSet(64,64, "./res/img/Tiles/Ground.png");
    TileMap* Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_ground",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-4);
    Tiles->Depth = DepthMode::Background;
    Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AboveGround",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-4);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AbovePlayer",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-3);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AbovePlayer2",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(100);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/Tiles/Ground.png");
    Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_collision",Tset);
    Map->LoadCollision("./res/map/v1/mapa_v1");
    Map->Enabled = false;
    CollisionMap = &(Map->_TileMatrix);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    // //Testing map
    // GameObject* Tiles = new GameObject();
    // Tiles->Depth = DepthMode::Background;

    // TileSet* Tset = new TileSet(64,64, "./res/img/Tiles/PradoSet.png");
    // TileMap* Map = new TileMap(*Tiles, "./res/map/pradomap_ground",Tset);
    
    // // TileSet* Tset = new TileSet(64,64, "./res/img/testSet.png");
    // // TileMap* Map = new TileMap(*Tiles, "./res/map/Tests_Floor",Tset);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    // Tiles = new GameObject(1);
    // Tiles->Depth = DepthMode::Background;
    
    // Tset = new TileSet(64,64, "./res/img/Tiles/PradoSet.png");
    // Map = new TileMap(*Tiles, "./res/map/pradomap_collision",Tset);
    // Map->LoadCollision("./res/map/pradomap_collision");
    // Map->Enabled = false;

    // // Tset = new TileSet(64,64, "./res/img/testSet.png");
    // // Map = new TileMap(*Tiles, "./res/map/Tests_Rocks",Tset);
    // // Map->LoadCollision("./res/map/Test_Rocks");
    // CollisionMap = &(Map->_TileMatrix);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    GameObject* Fader = new GameObject(200);
    Fader->Depth = DepthMode::Foreground;
    _Fader = new Fade(*Fader, Color("#00000000"), Color("#00000000"), 2);
    Fader->AddComponent(_Fader);
    Fader->AddComponent(new CameraFollower(*Fader));
    AddGameObj(Fader);


    GameObject* Loops = new GameObject(-10);
    LoopSprite* L = new LoopSprite(*Loops, "./res/img/Surface.png");
    L->SetAnimationData(4, 1, 4, 0.25f);
    Loops->AddComponent(L);
    AddGameObj(Loops);


    GameObject* Snd = new GameObject();
    Snd->Box.SetPosition(Vector2(1200,1200));
    Sound* Sd = new Sound(*Snd, "./res/audio/dirt.ogg");
    Sd->Pan = true;
    Sd->Play(100);
    Snd->AddComponent(Sd);
    Snd->AddComponent(new Sprite(*Snd, "./res/galor.png"));
    AddGameObj(Snd);
    
    
}

void Test01::PhysicsUpdate(float Dt)
{    
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
				 ||(((SceneGameObjects[i]->Represents & SceneGameObjects[j]->Interacts) //Activate once object masks are being used
				| (SceneGameObjects[j]->Represents & SceneGameObjects[i]->Interacts)) == CollisionMask::None) 
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
int _Type = 0;


void Test01::Update(float Dt)
{
    Input& input = Input::Instance();
    if(input.KeyJustPressed(Key::Equal))
    {
        _Type++;
        _Type = _Type > 15 ? 0 : _Type;
        std::cout <<_Type << '\n';
    }
    else if(input.KeyJustPressed(Key::Minus))
    {
        _Type--;
        _Type = _Type < 0 ? 15 : _Type;
        std::cout <<_Type << '\n';
    }
    if(input.MousePressedDown(MouseButton::Left))
    {
        Particle z;
        z.Type = _Type;
        z.Size =  Vector2(1,1);
        z.Position =  input.MousePosition();
        // z.Velocity =  Vector2(50,0);
        // z.Acceleration =  Vector2(0,300);
        z.Angle = 2.0f * M_PI * Engine::RandomFloat();
        z.RotationPerSec = 2.0f * M_PI * (Engine::RandomFloat()-0.5f);
        z.Spread = 3.1415f/2.0f;
        z.Duration = 4.0f;
        z.Windswept = true;
        z.ColorInterpolation = true;
        z.StartColor = Color("#00ff00ff");
        z.EndColor = Color("#00440088");
        ParticleManager::Instance().Emit(z);
    }


    if(text && Engine::Instance().GetPing())
    {
        text->SetText(std::to_string(1.0f/Dt) + " Fps");
    }

   
    if(Input::Instance().KeyJustPressed(Key::Number1))
    {
        GameObject* slimeObj = new GameObject();
        Slime* slime = new Slime(*slimeObj);
        slimeObj->Box.SetCenter(Input::Instance().MousePosition());
        slimeObj->AddComponent(slime);
        AddGameObj(slimeObj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number2) && Player::Self == nullptr)
    {
            GameObject* playerObj = new GameObject();
            Player* player = new Player(*playerObj);
            playerObj->Box.SetCenter(Vector2(640, 750));
            playerObj->AddComponent(player);
            AddGameObj(playerObj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number8))
    {
        _Fader->SetFinishColor(Color("#1228093a"));
    }
    if(Input::Instance().KeyJustPressed(Key::Number9))
    {
        _Fader->SetFinishColor(Color("#50148a33"));
    }
    if(Input::Instance().KeyJustPressed(Key::Number0))
    {
        _Fader->SetFinishColor(Color("#00000000"));
    }

    ParticleManager::Instance().Update(Dt);
    if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        text = nullptr;
    }
}

void Test01::Render()
{
    ParticleManager::Instance().Render();
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