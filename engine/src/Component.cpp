#include "../lib/Component.hpp"

Component::Component(GameObject& GameObj)
: Parent(GameObj)
{
    _Type = ComponentType::_None;
}

Component::~Component()
{
}

void Component::Render()
{
}

void Component::Start()
{
}

void Component::Collided(GameObject& Other)
{
}

void Component::PhysicsUpdate(float Dt)
{
}

void Component::Update(float Dt)
{
}

void Component::LateUpdate(float Dt)
{
}

bool Component::Is(std::string Type)
{
    return (Type == "Component");
}
bool Component::Is(ComponentType Type)
{
    return (Type == _Type);
}