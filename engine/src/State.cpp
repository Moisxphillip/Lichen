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
    StateGameObjects.clear(); //Gets rid of objects made
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
	StateGameObjects.insert(std::upper_bound(StateGameObjects.begin(), StateGameObjects.end(), NewGameObject->GetLayer(),
		[](int a, std::shared_ptr<GameObject> b){return a < b.get()->GetLayer();}), NewSharedObj); 

	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj);
	if(_Started)
	{
        NewWeakObj.lock()->Start(); //Make it start if it's added during state run
    }
	return NewWeakObj;
}

std::weak_ptr<GameObject> State::GetGameObjPtr(GameObject* ComparePtr)
{
    for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		if(StateGameObjects[i].get() == ComparePtr)
		{
			return StateGameObjects[i];
		}
	}
	return {};
}

void State::StateStart()
{
	Start();
    for(int i = 0; i< (int)(StateGameObjects.size()); i++)
    {
        StateGameObjects[i]->Start();
    }
    _Started = true;
}

void State::StatePhysicsUpdate(float Dt)
{
	PhysicsUpdate(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		StateGameObjects[i]->PhysicsUpdate(Dt);//Updates based on input and Dt
	}
}

void State::StateUpdate(float Dt)
{
	Update(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		StateGameObjects[i]->Update(Dt);//Updates based on input and Dt
	}
}

void State::StateLateUpdate(float Dt)
{
	Cam.Update(0);
	LateUpdate(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		StateGameObjects[i]->LateUpdate(Dt);//Updates based on input and Dt
	}
	
	for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		if(StateGameObjects[i]->IsDead())
		{
			StateGameObjects.erase(StateGameObjects.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void State::StateRender()
{
    for(int i = 0; i< (int)(StateGameObjects.size()); i++)
	{
		StateGameObjects[i]->Render(); //Calls render procedure for each existing GameObject
	}
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
