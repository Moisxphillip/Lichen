#include <memory>
#include <algorithm>
#include <iostream>

#include "../lib/State.hpp"

State::State()
{
    _QuitRequested = false;
    _PopRequested = false;
    _Started = false;
	// Cam.Position = Vector2(0,0);
}

State::~State()
{
    GameObjVec.clear(); //Gets rid of objects made
    LateRenderVec.clear(); //Gets rid of objects made
}

bool State::HasStarted()
{
    return _Started;
}

bool State::PopRequested()
{
    return _PopRequested;
}

bool State::QuitRequested()
{
    return _QuitRequested;
}

void State::RequestQuit()
{
	_QuitRequested = true;
}

std::weak_ptr<GameObject> State::AddGameObj(GameObject* NewGameObject)
{
	std::shared_ptr<GameObject> NewSharedObj(NewGameObject);
	GameObjVec.insert(std::upper_bound(GameObjVec.begin(), GameObjVec.end(), NewGameObject->GetLayer(),
		[](int a, std::shared_ptr<GameObject> b){return a < b.get()->GetLayer();}), NewSharedObj); 

	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj);
	if(_Started)
	{
        NewWeakObj.lock()->Start(); //Make it start if it's added during state run
    }
	return NewWeakObj;
}

std::weak_ptr<GameObject> State::AddLateRenderObj(GameObject* NewGameObject)
{
    std::shared_ptr<GameObject> NewSharedObj(NewGameObject);

	LateRenderVec.push_back(NewSharedObj);//Stores new pointer on Late Render vector
	if(_Started)
	{
        LateRenderVec[LateRenderVec.size()-1]->Start(); //Make it start if it's added during state run
    }
	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj) ;
	return NewWeakObj;
}

std::weak_ptr<GameObject> State::GetGameObjPtr(GameObject* ComparePtr)
{
    for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(GameObjVec[i].get() == ComparePtr)
		{
			return GameObjVec[i];
		}
	}
	return {};
}

std::weak_ptr<GameObject> State::GetLateRenderObjPtr(GameObject* ComparePtr)
{
    for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		if(LateRenderVec[i].get() == ComparePtr)
		{
			return LateRenderVec[i];
		}
	}
	return {};
}

void State::StateStart()
{
	Start();
    for(int i = 0; i< (int)(GameObjVec.size()); i++)
    {
        GameObjVec[i]->Start();
    }
    _Started = true;
}

void State::StatePhysicsUpdate(float Dt)
{
	PhysicsUpdate(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->PhysicsUpdate(Dt);//Updates based on input and Dt
	}

	//Late Render Updates
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->PhysicsUpdate(Dt); //Calls render procedure for the late stuff
	}
}

void State::StateUpdate(float Dt)
{
	Update(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->Update(Dt);//Updates based on input and Dt
	}

	//Late Render Updates
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->Update(Dt); //Calls render procedure for the late stuff
	}
}

void State::StateLateUpdate(float Dt)
{
	Cam.Update(0);
	LateUpdate(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->LateUpdate(Dt);//Updates based on input and Dt
	}
	
	for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		if(GameObjVec[i]->IsDead())
		{
			GameObjVec.erase(GameObjVec.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}

	//Late Render Updates
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->LateUpdate(Dt); //Calls render procedure for the late stuff
	}

	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		if(LateRenderVec[i]->IsDead())
		{
			LateRenderVec.erase(LateRenderVec.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void State::StateRender()
{
    for(int i = 0; i< (int)(GameObjVec.size()); i++)
	{
		GameObjVec[i]->Render(); //Calls render procedure for each existing GameObject
	}
	
	for(int i = 0; i< (int)(LateRenderVec.size()); i++)
	{
		LateRenderVec[i]->Render(); //Calls render procedure for the late stuff
	}
	Render();
}

void State::StatePause()
{
	Pause();
}

void State::StateResume()
{
	Resume();
}

void State::Start()
{
}

void State::Pause()
{
}

void State::Resume()
{
}

void State::LoadAssets()
{
}

void State::PhysicsUpdate(float Dt)
{
}

void State::Update(float Dt)
{
}

void State::LateUpdate(float Dt)
{
}

void State::Render()
{
}
