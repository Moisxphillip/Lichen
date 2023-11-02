#ifndef GAME_PLAYER
#define GAME_PLAYER

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Tools/Timer.hpp"

#include "Attack.hpp"

class Player : public StateMachine
{
    private:
        Timer _HitCooldown;

    public:
        AACircle* MyCollider;
        static Player* Self;
        Player(GameObject& Parent, std::string Label = "Player");
        ~Player();
        void SMStart();
        void SMPhysicsUpdate(float Dt);
        void SMUpdate(float Dt);
        void OnCollision(GameObject& Other);        
};

//-------------------------------------------States----------------------------------------------

//Idle
class PlayerIdle : public GenericState
{
    private:

    public:
    PlayerIdle(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};

//Walk
class PlayerWalk : public GenericState
{
    private:

    public:
    PlayerWalk(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};

//Walk
class PlayerDash : public GenericState
{
    private:
    int _DashForce;
    Timer _DashTime;

    public:
    PlayerDash(const StateInfo& Specs);
    void Start();
    void OnCollision(StateMachine& Sm, GameObject& Other);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
    void Update(StateMachine& Sm, float Dt);
};

#endif//GAME_PLAYER