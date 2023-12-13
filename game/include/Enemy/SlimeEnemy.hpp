
#ifndef LICHEN_SLIME_ENEMY
#define LICHEN_SLIME_ENEMY

#include "Enemy/Enemy.hpp"

class Slime: public Enemy
{
private:
    float _LeapSpeed;

public:
    Slime(GameObject& Parent, std::string Label = "Enemy", Stats EnemyStats = DEFAULT_STATS);

    float GetLeapSpeed();
    void SetLeapSpeed(float LeapSpeed);
    void SMOnCollision(GameObject& Other);
};

class SlimeAttack : public EnemyAttack 
{
    private:
        bool _HasAttacked;
        Vector2 _DirectionLeap;

    public:
        SlimeAttack(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
};


#endif





