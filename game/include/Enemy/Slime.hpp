#ifndef GAME_SLIME
#define GAME_SLIME

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Math/Vector2.hpp"

//The core entity
class Slime : public StateMachine
{
    private:

    public:
        AACircle* MyCollider;
        Slime(GameObject& Parent, std::string Label = "Slime");
        void SMStart();
        Vector2 Target;
};

//Idle state
class SlimeIdle : public GenericState
{
    private:

    public:
    SlimeIdle(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};

//Walk state
class SlimeWalk : public GenericState
{
    private:

    public:
    SlimeWalk(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};

#endif//GAME_SLIME