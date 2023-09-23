#include "../lib/StageScene.hpp"
#include "../lib/EndScene.hpp"
#include "../lib/GameStats.hpp"
#include "../lib/PenguinBody.hpp"
#include "../lib/Alien.hpp"
#include "../lib/Path.hpp"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/CameraFollower.hpp"
#include "../../engine/lib/Collision.hpp"
#include "../../engine/lib/Fade.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/TileSet.hpp"
#include "../../engine/lib/TileMap.hpp"

#define LICHEN_TILEWIDTH 64
#define LICHEN_TILEHEIGHT 64


StageScene::StageScene()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
    _SceneMusic = nullptr; 
    _QuitFade = false;
	_Started = false;
	//Init random machine
    Rng.seed(5);
	Rng.range(0,1000);
}

StageScene::~StageScene()
{
    delete _SceneMusic;
    _SceneMusic = nullptr;
}

void StageScene::Start()
{
	LoadAssets();
}

void StageScene::Pause()
{
}

void StageScene::Resume()
{
}

void StageScene::LoadAssets()
{
	//Basic state elements
    GameObject *BgElement = new GameObject(0);//Create a gameobject to be associated with the background sprite 
    Sprite* SceneBg = new Sprite(*BgElement, FIMG_OCEAN);//Load image background
	CameraFollower *FixedBg = new CameraFollower(*BgElement);
	BgElement->AddComponent(SceneBg); //registers component on the gameObject
	BgElement->AddComponent(FixedBg); //Keeps initial coordinates fixed on camera
	BgElement->Box.Redimension(Vector2(SceneBg->GetWidth(),SceneBg->GetHeight()));//Sets dimensions for the background GameObject
	AddGameObj(BgElement);//Stores GameObject on scene GameObj vector

	//Init TileMap
	GameObject* SceneMap = new GameObject(1);
	TileSet* SceneTileSet = new TileSet(LICHEN_TILEWIDTH, LICHEN_TILEHEIGHT, FIMG_TILESET);
	TileMap* SceneTileMap = new TileMap(*SceneMap, FMAP_TILEMAP0, SceneTileSet, false, true);
	SceneMap->AddComponent(SceneTileMap);
	AddGameObj(SceneMap);
	
	//Init layer over map
	SceneMap = new GameObject(10);
	SceneMap->Depth = DepthMode::Foreground;
	SceneTileSet = new TileSet(LICHEN_TILEWIDTH, LICHEN_TILEHEIGHT, FIMG_TILESET);
	SceneTileMap = new TileMap(*SceneMap, FMAP_TILEMAP1, SceneTileSet, false, true);
	SceneTileMap->SetParallax(1.5);
	SceneMap->AddComponent(SceneTileMap);
	AddGameObj(SceneMap);

	//Penguin
	GameObject* PenguinObj = new GameObject(2);
	PenguinBody* Penguin = new PenguinBody(*PenguinObj);
	PenguinObj->Box.SetCenter(Vector2(100,100));
	PenguinObj->AddComponent(Penguin);
	AddGameObj(PenguinObj);
	Cam.Follow(PenguinObj);
	
	// Alien
	XrandU64 X, Y, N;
	X.seed(rand());
	Y.seed(rand());
	N.seed(rand());
	X.range(0, 1408);
	Y.range(0, 1280);

	for(int i = 0; i<5; i++)
	{
		GameObject* AlienObj = new GameObject(3);
		Alien* Et = new Alien(*AlienObj, 4+(N.gen()%4));
		AlienObj->Box.SetCenter(Vector2(X.gen(),Y.gen()));
		AlienObj->AddComponent(Et);
		AddGameObj(AlienObj);
	}
	// //Play music
	_SceneMusic = new Music(FMUS_STAGE1);//Load the music file for the current state
	_SceneMusic->Play(-1, 1000); //Start playing phase theme
}

void StageScene::Update(float Dt)
{
	//Sets QuitFade flag if Esc or close button were pressed
	if((!_QuitFade && (Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested()))) 
	{
		_SceneMusic->Stop(0);
		_QuitFade = true;
		_QuitRequested = true;
	}

	if(_QuitFade && !Mix_PlayingMusic())//Ensures fadeout finishes before closing
	{
		if(Alien::AlienCount == 0 || PenguinBody::Player == nullptr)
		{
			EndScene* Ended = new EndScene();
			Engine::Instance().Push(Ended);
		}
		_PopRequested = true;
	}

	if(Input::Instance().KeyJustPressed(Key::Number1))
	{
		_SceneMusic->Stop(1000);
		GameStats::PlayerVictory = true;
		_QuitFade = true;
	}
	if(Input::Instance().KeyJustPressed(Key::O))
	{
		Window& X = Engine::Instance().GetWindow();
		glm::mat4 Proj =  glm::ortho(0.0f, (float)X.GetWidth(), (float)X.GetHeight(), 0.0f, -1000.0f, 1000.0f);
		X.SetProjection(Proj);
	}
	if(Input::Instance().KeyJustPressed(Key::P))
	{
		Window& X = Engine::Instance().GetWindow();
		glm::mat4 Proj =  glm::perspective(glm::radians(45.0f), (float)X.GetWidth()/(float)X.GetHeight(), 0.1f, 1000.0f);
		X.SetProjection(Proj);
	}

	if(Alien::AlienCount == 0 && !_QuitFade)
	{
		_SceneMusic->Stop(1000);
		GameStats::PlayerVictory = true;
		_QuitFade = true;
	}
	else if(PenguinBody::Player == nullptr && !_QuitFade)
	{
		_SceneMusic->Stop(1000);
		GameStats::PlayerVictory = false;
		_QuitFade = true;
	}

	if(!_QuitFade && !Mix_PlayingMusic())
	{
		_QuitFade = true;
	}
		
	//TODO transfer to Scene, add the masks to it
	for(int i = 0; i< (int)SceneGameObjects.size()-1; i++)
	{
		if(!SceneGameObjects[i]->Contains(ComponentType::Collider))
		{
			continue;
		}

		Component* ColA = SceneGameObjects[i]->GetComponent(ComponentType::Collider);
		for(int j = i+1; j < (int)SceneGameObjects.size(); j++)
		{

			if(!SceneGameObjects[j]->Contains(ComponentType::Collider) /*|| //Activate once object masks are being used
				(((SceneGameObjects[i]->Represents & SceneGameObjects[j]->Interacts) 
				| (SceneGameObjects[j]->Represents & SceneGameObjects[i]->Interacts)) 
				== CollisionMask::None)*/)
			{
				continue;
			}

			Component* ColB = SceneGameObjects[j]->GetComponent(ComponentType::Collider);
			if(Collision::IsColliding(SceneGameObjects[i]->Box, SceneGameObjects[j]->Box, SceneGameObjects[i]->Angle, SceneGameObjects[j]->Angle))
			{
				SceneGameObjects[i]->OnCollision(*SceneGameObjects[j]);
				SceneGameObjects[j]->OnCollision(*SceneGameObjects[i]);
			}
		}
	}
}

void StageScene::Render()
{

}

