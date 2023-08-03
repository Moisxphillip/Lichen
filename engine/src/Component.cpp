#include "../lib/Component.hpp"

Component::Component(GameObject& GameObj)
: GameObjAssoc(GameObj)
{
    // ComponentFlags = Uses::None;
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

void Component::Update(float Dt)
{
}

bool Component::Is(std::string Type)
{
    return (Type == "Component");
}