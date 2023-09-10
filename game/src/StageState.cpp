#include "../lib/StageState.hpp"
#include "../lib/EndState.hpp"
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


StageState::StageState()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
    _StateMusic = nullptr; 
    _QuitFade = false;
	_Started = false;
	//Init random machine
    Rng.seed(5);
	Rng.range(0,1000);
}

StageState::~StageState()
{
    delete _StateMusic;
    _StateMusic = nullptr;
}

void StageState::Start()
{
	LoadAssets();
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}

void StageState::LoadAssets()
{
	//Basic state elements
    GameObject *BgElement = new GameObject(0);//Create a gameobject to be associated with the background sprite 
    Sprite* StateBg = new Sprite(*BgElement, FIMG_OCEAN);//Load image background
	CameraFollower *FixedBg = new CameraFollower(*BgElement);
	BgElement->AddComponent(StateBg); //registers component on the gameObject
	BgElement->AddComponent(FixedBg); //Keeps initial coordinates fixed on camera
	BgElement->Box.Redimension(Vector2(StateBg->GetWidth(),StateBg->GetHeight()));//Sets dimensions for the background GameObject
	AddGameObj(BgElement);//Stores GameObject on scene GameObj vector

	//Init TileMap
	GameObject* StateMap = new GameObject(1);
	TileSet* StateTileSet = new TileSet(LICHEN_TILEWIDTH, LICHEN_TILEHEIGHT, FIMG_TILESET);
	TileMap* StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP0, StateTileSet, false, true);
	StateMap->AddComponent(StateTileMap);
	AddGameObj(StateMap);
	
	//Init layer over map
	StateMap = new GameObject(10);
	StateMap->Depth = DepthMode::Foreground;
	StateTileSet = new TileSet(LICHEN_TILEWIDTH, LICHEN_TILEHEIGHT, FIMG_TILESET);
	StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP1, StateTileSet, false, true);
	StateTileMap->SetParallax(1.5);
	StateMap->AddComponent(StateTileMap);
	AddGameObj(StateMap);

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
	_StateMusic = new Music(FMUS_STAGE1);//Load the music file for the current state
	_StateMusic->Play(-1, 1000); //Start playing phase theme
}

void StageState::Update(float Dt)
{
	//Sets QuitFade flag if Esc or close button were pressed
	if((!_QuitFade && (Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested()))) 
	{
		_StateMusic->Stop(0);
		_QuitFade = true;
		_QuitRequested = true;
	}

	if(_QuitFade && !Mix_PlayingMusic())//Ensures fadeout finishes before closing
	{
		if(Alien::AlienCount == 0 || PenguinBody::Player == nullptr)
		{
			EndState* Ended = new EndState();
			Engine::Instance().Push(Ended);
		}
		_PopRequested = true;
	}

	if(Input::Instance().KeyJustPressed(Key::Number1))
	{
		_StateMusic->Stop(1000);
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
		_StateMusic->Stop(1000);
		GameStats::PlayerVictory = true;
		_QuitFade = true;
	}
	else if(PenguinBody::Player == nullptr && !_QuitFade)
	{
		_StateMusic->Stop(1000);
		GameStats::PlayerVictory = false;
		_QuitFade = true;
	}

	if(!_QuitFade && !Mix_PlayingMusic())
	{
		_QuitFade = true;
	}
		
	//TODO transfer to State, add the masks to it
	for(int i = 0; i< (int)StateGameObjects.size()-1; i++)
	{
		if(!StateGameObjects[i]->Contains(ComponentType::Collider))
		{
			continue;
		}

		Component* ColA = StateGameObjects[i]->GetComponent(ComponentType::Collider);
		for(int j = i+1; j < (int)StateGameObjects.size(); j++)
		{

			if(!StateGameObjects[j]->Contains(ComponentType::Collider) /*|| //Activate once object masks are being used
				(((StateGameObjects[i]->Represents & StateGameObjects[j]->Interacts) 
				| (StateGameObjects[j]->Represents & StateGameObjects[i]->Interacts)) 
				== CollisionMask::None)*/)
			{
				continue;
			}

			Component* ColB = StateGameObjects[j]->GetComponent(ComponentType::Collider);
			if(Collision::IsColliding(StateGameObjects[i]->Box, StateGameObjects[j]->Box, StateGameObjects[i]->Angle, StateGameObjects[j]->Angle))
			{
				StateGameObjects[i]->OnCollision(*StateGameObjects[j]);
				StateGameObjects[j]->OnCollision(*StateGameObjects[i]);
			}
		}
	}
}

void StageState::Render()
{

}

