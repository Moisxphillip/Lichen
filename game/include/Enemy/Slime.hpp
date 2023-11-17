#ifndef GAME_SLIME
#define GAME_SLIME

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Math/Vector2.hpp"

#include <queue>

//The core entity
class Slime : public StateMachine
{
    private:

    public:
        AACircle* MyCollider;
        Slime(GameObject& Parent, std::string Label = "Slime");
        ~Slime();
        void MoveTo(Vector2 Destiny, float Dt);
        void SMStart();
        void SMOnCollision(GameObject& Other);
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
        std::queue<Vector2> Path;
    public:
        SlimeWalk(const StateInfo& Specs);
        void Start();
        void PhysicsUpdate(StateMachine& Sm, float Dt);
};

#endif//GAME_SLIME