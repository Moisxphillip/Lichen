#define _USE_MATH_DEFINES
#include <cmath>

#include "Core/GameObject.hpp"
#include "Components/Component.hpp"
#include "Math/Rectangle.hpp"
#include "Tools/Tools.hpp"
//TODO future improvement: sort component vector on new addition, implement binary search for Get/Remove;

unsigned int GameObject::_ID = 0;

GameObject::GameObject(int Layer)
{
    Box = Rectangle(0,0,0,0); //Inits Object rectangle
    _GameObjDead = false;//Sets as alive for future checks in the gameObject lifetime
    Started = false;
    Angle = 0;
    _Layer = Layer;
    Depth = DepthMode::Background;
    Represents = CollisionMask::None;
    Interacts = CollisionMask::None;
    _Contains = ComponentType::None;
    _UID = _ID;
    _ID++;
}

GameObject::GameObject()
: GameObject(0)
{
}

GameObject::~GameObject()
{
    _GameObjComponents.clear();//Removes all components 
}

void GameObject::Start()
{
    for(int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Start();
    }
    Started = true;
}

void GameObject::PhysicsUpdate(float Dt)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->PhysicsUpdate(Dt);//Calls update from each component belonging to this GameObject
    }
}

void GameObject::Update(float Dt)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Update(Dt);//Calls update from each component belonging to this GameObject
    }
}

void GameObject::LateUpdate(float Dt)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->LateUpdate(Dt);//Calls update from each component belonging to this GameObject
    }

    if(Angle< -M_PI || Angle >M_PI)//Wrapper for avoiding unlimited growth
    {
        Angle = WrapMinMax(Angle, -M_PI, M_PI);
    }
}

void GameObject::OnCollision(GameObject& Other)
{
    for(int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->OnCollision(Other);
    }
}

void GameObject::Render()
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        _GameObjComponents[i]->Render();//Call render for each component belonging to this GameObject
    }
}

bool GameObject::IsDead()
{
    return _GameObjDead;
}

void GameObject::RequestDelete()
{
    _GameObjDead = true; //Sets object as ready for deletion
}

void GameObject::AddComponent(Component* GameComponent)
{
    _Contains = _Contains | GameComponent->Type();
    _GameObjComponents.emplace_back(GameComponent); //Stores components belonging to current GameObject
}

void GameObject::RemoveComponent(Component* GameComponent)
{
    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        if(_GameObjComponents[i].get() == GameComponent)
        {
            _Contains = _Contains ^ GameComponent->Type();
            _GameObjComponents.erase(_GameObjComponents.begin()+i); //Removal of an specific component identified by its pointer
            return;
        }
    }
}

Component* GameObject::GetComponent(ComponentType ComponentEnum)
{
    if((ComponentEnum & _Contains) == ComponentType::None)
    {
        return nullptr; //Nothing has been found
    }

    for (int i = 0; i < (int)(_GameObjComponents.size()); i++)
    {
        if(_GameObjComponents[i]->Is(ComponentEnum))
        {
            return _GameObjComponents[i].get(); //Get the pointer of the 1st component from a given type found on the Component array
        }
    }
    
    return nullptr; //so the compiler won't cry
}

bool GameObject::Contains(ComponentType GO)
{
    return static_cast<bool>(GO & _Contains);
}

int GameObject::GetLayer()
{
    return _Layer;
}

void GameObject::SetLayer(int Layer)
{
    _Layer = Layer;
}

int GameObject::GetUID() const
{
    return _UID;
}

std::ostream& operator<<(std::ostream& Out, const GameObject& Other)
{
    Out << "GameObject: " << Other.GetUID();
    return Out;
}