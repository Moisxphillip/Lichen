#include "Tools/Emitter.hpp"
#include "Core/Engine.hpp"

Emitter::Emitter(GameObject& Parent, float Time, Vector2 Spread, bool DeleteAfter)
: Component(Parent), _Spread(Spread), _Delete(DeleteAfter)
{
    _ToEmit.SetLimit(Time);
    _ToEmit.Restart();
}

void Emitter::Update(float Dt)
{
    _ToEmit.Update(Dt);
    if(_ToEmit.Finished())
    {
        GameObject* GO = nullptr;
        if(_Emit)
        {
            GO = _Emit(Parent.Box.Position() + Vector2(_Spread.x * Engine::RandomFloat(), _Spread.y * Engine::RandomFloat()));
            if(GO != nullptr)
            {
                Engine::Instance().CurrentScene().AddGameObj(GO);
            }
        }
        if(_Delete)
        {
            Parent.RequestDelete();
            return;
        }
        _ToEmit.Restart();
    }
}
