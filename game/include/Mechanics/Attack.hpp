#ifndef GAME_ATTACK
#define GAME_ATTACK

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Mechanics/Combat.hpp"

class Attack: public Component
{
    private:
        bool _SelfDestruct;
        bool _HitDestruct;
        float _AfterHitLifeTime;
        Timer _LifeTime;

    public:
        Stats Attacker;
        AttackData Data;
        Attack(GameObject& Parent, 
            Stats Attacker, 
            AttackData Data, 
            CollisionMask Target, 
            float LifeTime=0.0f, 
            float AfterHitLifeTime=0.0f);
            
        void Update(float Dt);
        void OnCollision(GameObject& Other);    
};

#endif//GAME_ATTACK