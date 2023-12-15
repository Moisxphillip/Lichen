#include "Tools/OnDelete.hpp"
#include "Core/Engine.hpp"

OnDelete::OnDelete(GameObject& Parent, std::function<void()> ToDo)
: Component(Parent), ToDo(ToDo)
{
}

OnDelete::~OnDelete()
{
    if(Engine::Instance().CurrentScene().PopRequested() || Engine::Instance().CurrentScene().QuitRequested())
    {
        return;
    }
    ToDo();
}
