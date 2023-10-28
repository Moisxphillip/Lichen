#ifndef GAME_ATTACK
#define GAME_ATTACK

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Combat.hpp"

class Attack: public Component
{
    private:
        bool _SelfDestruct;
        bool _HitDestruct;
        float _AfterHitLifeTime;
        Timer _LifeTime;

    public:
        AttackData Data;
        Attack(GameObject& Parent, AttackData Data, CollisionMask Target, float LifeTime=0.0f, float AfterHitLifeTime=0.0f);
        void Update(float Dt);
        bool Is(ComponentType Type);
        void OnCollision(GameObject& Other);    
};

#endif//GAME_ATTACK