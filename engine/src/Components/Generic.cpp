#include "Components/Generic.hpp"

Generic::Generic(GameObject& GameObj, std::string Name)
: Component(GameObj), Angle(Parent.Angle), Box(Parent.Box)
{
    _Name = Name;
    this->Started = false;
    _Render = nullptr;
    _Start = nullptr;
    _Update = nullptr;
    _Type = ComponentType::Generic;
}

void Generic::SetRender(void(*Render)(Generic*))
{
    _Render = Render;
}

void Generic::SetStart(void(*Start)(Generic*))
{
    _Start = Start;
}

void Generic::SetUpdate(void(*Update)(float, Generic*))
{
    _Update = Update;
}

void Generic::RequestDelete()
{
    this->Parent.RequestDelete();
}

void Generic::Render()
{
    if(_Render != nullptr)
    {
        _Render(this);
    }
}

void Generic::Start()
{

    if(_Start != nullptr)
    {
        _Start(this);
        this->Started = true;
    }
}

void Generic::Update(float Dt)
{
    if(_Update != nullptr)
    {
        _Update(Dt, this);
    }
}

std::string Generic::GetName()
{
    return _Name;
}