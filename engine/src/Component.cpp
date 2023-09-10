#include "../lib/Component.hpp"

Component::Component(GameObject& GameObj)
: Parent(GameObj)
{
    _Type = ComponentType::None;
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

void Component::OnCollision(GameObject& Other)
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

ComponentType Component::Type()
{
    return _Type;
}

bool Component::Is(ComponentType Type)
{
    return (Type == _Type);
}