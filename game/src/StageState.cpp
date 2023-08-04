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
#include "../../engine/lib/ScreenFade.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/TileSet.hpp"
#include "../../engine/lib/TileMap.hpp"

#define LICHEN_TILEWIDTH 64
#define LICHEN_TILEHEIGHT 64

ScreenFade* Screener = nullptr;

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

    GameObjVec.clear(); //Gets rid of objects made
    LateRenderVec.clear(); //Gets rid of objects made
}

void StageState::Start()
{
	LoadAssets();
	// StateStart();
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
    GameObject *BgElement = new GameObject;//Create a gameobject to be associated with the background sprite 
    Sprite* StateBg = new Sprite(*BgElement, FIMG_OCEAN);//Load image background
	CameraFollower *FixedBg = new CameraFollower(*BgElement);
	BgElement->AddComponent(StateBg); //registers component on the gameObject
	BgElement->AddComponent(FixedBg); //Keeps initial coordinates fixed on camera
	BgElement->Box.Redimension(Vector2(StateBg->GetWidth(),StateBg->GetHeight()));//Sets dimensions for the background GameObject
	AddGameObj(BgElement);//Stores GameObject on scene GameObj vector

	//Init TileMap
	GameObject* StateMap = new GameObject();
	TileSet* StateTileSet = new TileSet(LICHEN_TILEWIDTH, LICHEN_TILEHEIGHT, FIMG_TILESET);
	TileMap* StateTileMap = new TileMap(*StateMap, FMAP_TILEMAP, StateTileSet);
	StateMap->AddComponent(StateTileMap);
	AddGameObj(StateMap);
	AddLateRenderObj(StateMap);

	//Penguin
	GameObject* PenguinObj = new GameObject();
	PenguinBody* Penguin = new PenguinBody(*PenguinObj);
	PenguinObj->Box.SetCenter(Vector2(100,100));
	PenguinObj->AddComponent(Penguin);
	AddGameObj(PenguinObj);
	Cam.Follow(PenguinObj);
	
	//Alien
	XrandU64 X, Y, N;
	X.seed(rand());
	Y.seed(rand());
	N.seed(rand());
	X.range(0, 1408);
	Y.range(0, 1280);

	for(int i = 0; i<5; i++)
	{
		GameObject* AlienObj = new GameObject();
		Alien* Et = new Alien(*AlienObj, 4+(N.gen()%4));
		AlienObj->Box.SetCenter(Vector2(X.gen(),Y.gen()));
		AlienObj->AddComponent(Et);
		AddGameObj(AlienObj);
	}
	//Play music
	_StateMusic = new Music(FMUS_STAGE1);//Load the music file for the current state
	_StateMusic->Play(-1, 1000); //Start playing phase theme
}

void StageState::Update(float Dt)
{
	//Sets QuitFade flag if Esc or close button were pressed
	if((!_QuitFade && (Input::Instance().IsKeyDown(K_ESC) || Input::Instance().QuitRequested()))) 
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
		Screener = nullptr;
		_PopRequested = true;
	}

	if(Input::Instance().KeyPress(SDLK_1))
	{
		_StateMusic->Stop(1000);
		GameStats::PlayerVictory = true;
		_QuitFade = true;
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

	if(Input::Instance().KeyPress(K_P))
	{
		if(Screener == nullptr)
		{
			GameObject* ScreenObj = new GameObject();
			ScreenFade* Scr = new ScreenFade(*ScreenObj, Color("#000000"),0.0, 0.9, 2);
			ScreenObj->AddComponent(Scr);
			AddLateRenderObj(ScreenObj);
			Screener = Scr;
		}
	}
	if(Input::Instance().KeyPress(SDLK_MINUS))
	{
		if(Screener != nullptr)
		{
			Screener->RedirectFade(0.1);
		}
	}
	else if(Input::Instance().KeyPress(SDLK_EQUALS))
	{
		if(Screener != nullptr)
		{
			Screener->RedirectFade(0.9);
		}
	}


	// Cam.Update(Dt);
		
	for(int i = 0; i< (int)GameObjVec.size()-1; i++)
	{
		Component* ColA = GameObjVec[i]->GetComponent("Collider");
		if(ColA != nullptr)
		{
			for(int j = i+1; j < (int)GameObjVec.size(); j++)
			{
				Component* ColB = GameObjVec[j]->GetComponent("Collider");
				if(ColB != nullptr)
				{
					if(Collision::IsColliding(GameObjVec[i]->Box, GameObjVec[j]->Box, GameObjVec[i]->Angle, GameObjVec[j]->Angle))
					{
						GameObjVec[i]->Collided(*GameObjVec[j]);
						GameObjVec[j]->Collided(*GameObjVec[i]);
					}
				}
			}
		}
	}
	//Calls updates for contained objects and remove dead objects
	// StateUpdate(Dt);

}


void StageState::Render()
{
	// StateRender();
}