#include "Tools/Emitter.hpp"
#include "Core/Engine.hpp"

Emitter::Emitter(GameObject& Parent, float Time, Vector2 Spread, bool DeleteAfter)
: Component(Parent), _Spread(Spread), _Delete(DeleteAfter), _Time(Time)
{
    _ToEmit.SetLimit(_Time + _Time/5.0f*Engine::RandomFloat());
    _ToEmit.Restart();
    Parent.Box.Redimension(Spread);
    Centered = false;
}

void Emitter::SetEmitCall(std::function<GameObject*(Vector2)> Function)
{
    _Emit = Function;
}

void Emitter::Update(float Dt)
{
    _ToEmit.Update(Dt);
    if(_ToEmit.Finished())
    {
        GameObject* GO = nullptr;
        if(_Emit)
        {
            Vector2 Pos = Centered ? Parent.Box.Center() : Parent.Box.Position();
            GO = _Emit(Pos + Vector2(_Spread.x * Engine::RandomFloat(), _Spread.y * Engine::RandomFloat()));
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
        _ToEmit.SetLimit(_Time + _Time/5.0f*Engine::RandomFloat());
        _ToEmit.Restart();
    }
}
