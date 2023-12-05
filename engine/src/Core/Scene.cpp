#include <memory>
#include <algorithm>
#include <iostream>

#include "Core/Scene.hpp"
#include "Math/Physics.hpp"

Scene::Scene()
{
    _QuitRequested = false;
    _PopRequested = false;
    _Started = false;
}

Scene::~Scene()
{
    SceneGameObjects.clear(); //Gets rid of objects made
}

bool Scene::HasStarted()
{
    return _Started;
}

bool Scene::PopRequested()
{
    return _PopRequested;
}

bool Scene::QuitRequested()
{
    return _QuitRequested;
}

void Scene::RequestQuit()
{
	_QuitRequested = true;
}

std::weak_ptr<GameObject> Scene::AddGameObj(GameObject* NewGameObject)
{
	std::shared_ptr<GameObject> NewSharedObj(NewGameObject);
	SceneGameObjects.insert(std::upper_bound(SceneGameObjects.begin(), SceneGameObjects.end(), NewGameObject->GetLayer(),
		[](int a, std::shared_ptr<GameObject> b){return a < b.get()->GetLayer();}), NewSharedObj); 

	std::weak_ptr<GameObject> NewWeakObj(NewSharedObj);
	if(_Started)
	{
        NewWeakObj.lock()->Start(); //Make it start if it's added during state run
    }
	return NewWeakObj;
}

std::weak_ptr<GameObject> Scene::GetGameObjPtr(GameObject* ComparePtr)
{
    for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		if(SceneGameObjects[i].get() == ComparePtr)
		{
			return SceneGameObjects[i];
		}
	}
	return {};
}

void Scene::SceneStart()
{
	Start();
    for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
    {
        SceneGameObjects[i]->Start();
    }
    _Started = true;
}

void Scene::ScenePhysicsUpdate(float Dt)
{
	PhysicsUpdate(Dt);

	//Collision detection
	for(int i = 0; i< (int)SceneGameObjects.size()-1; i++)
	{
		if(!SceneGameObjects[i]->Contains(ComponentType::AACollider))
		{
			continue;
		}

		AACollider* ColA = (AACollider*)SceneGameObjects[i]->GetComponent(ComponentType::AACollider);
		if(!ColA->Active)
		{
			continue;
		}
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
            if(!ColB->Active)
            {
                continue;
            }
			if((Physics::CheckCollision(*ColA, *ColB)))
			{
                Physics::ResolveCollision(*ColA, *ColB);
				SceneGameObjects[i]->OnCollision(*SceneGameObjects[j]);
				SceneGameObjects[j]->OnCollision(*SceneGameObjects[i]);
			}
		}
	}

	//Engine Object Updates
	for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		SceneGameObjects[i]->PhysicsUpdate(Dt);//Updates based on input and Dt
	}
}

void Scene::SceneUpdate(float Dt)
{
	Update(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		SceneGameObjects[i]->Update(Dt);//Updates based on input and Dt
	}
}

void Scene::SceneLateUpdate(float Dt)
{
	Cam.Update(0);
	LateUpdate(Dt);
	//Engine Object Updates
	for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		SceneGameObjects[i]->LateUpdate(Dt);//Updates based on input and Dt
	}
	
	for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		if(SceneGameObjects[i]->IsDead())
		{
			SceneGameObjects.erase(SceneGameObjects.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void Scene::SceneRender()
{
	std::stable_sort(SceneGameObjects.begin(), SceneGameObjects.end(), [](const std::shared_ptr<GameObject> A, const std::shared_ptr<GameObject> B) 
	{
		if (A->Depth < B->Depth)
        	return true;
		if (A->Depth > B->Depth)
			return false;
		if (A->Depth == DepthMode::Dynamic && B->Depth == DepthMode::Dynamic)
		{
			return A->Box.y + A->Box.h < B->Box.y + B->Box.h;
		}
		return A->GetLayer() < B->GetLayer();
	});

    for(int i = 0; i< (int)(SceneGameObjects.size()); i++)
	{
		SceneGameObjects[i]->Render(); //Calls render procedure for each existing GameObject
	}
	Render();
}

void Scene::ScenePause()
{
	Pause();
}

void Scene::SceneResume()
{
	Resume();
}

void Scene::Start()
{
}

void Scene::Pause()
{
}

void Scene::Resume()
{
}

void Scene::LoadAssets()
{
}

void Scene::PhysicsUpdate(float Dt)
{
}

void Scene::Update(float Dt)
{
}

void Scene::LateUpdate(float Dt)
{
}

void Scene::Render()
{
}
