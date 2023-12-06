#ifndef GAME_EMITTER
#define GAME_EMITTER

#include <functional>

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"

class Emitter : public Component
{
    private:
        bool _Delete;
        Timer _ToEmit;
        Vector2 _Spread;
        std::function<GameObject*(Vector2 Position)> _Emit;
    public:
        Emitter(GameObject& Parent, float Time, Vector2 Spread, bool DeleteAfter = false);
        void SetEmitCall(std::function<GameObject*()> Function);
        void Update(float Dt);

};

#endif//GAME_EMITTER