#ifndef GAME_MALACHI
#define GAME_MALACHI

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Mechanics/Combat.hpp"

class Malachi : public StateMachine
{
    private:
        Timer _HitCooldown;
        float _FlickTime;
        bool _Flick;
        
    public:
        static Malachi* Self;
        GameObject* Arena[5];
        Stats MyStats;
        AACircle* MyCollider;
        Malachi(GameObject& Parent, std::string Label = "Malachi");
        ~Malachi();
        void SMStart();
        void SMUpdate(float Dt);
        void SMOnCollision(GameObject& Other);
        void SetupArena();
};

//Idle state
class MalachiIdle : public GenericState
{
    private:
        Timer _ChangeState;

    public:
        void Start();
        MalachiIdle(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};


//Attack down state
class MalachiAtkDown : public GenericState
{
    private:

    public:
        MalachiAtkDown(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};

//Horiz Atk state
class MalachiAtkHoriz : public GenericState
{
    private:
        Timer _AtkTime;
    public:
        MalachiAtkHoriz(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};

//Pose state
class MalachiTeleportPose : public GenericState
{
    private:
        Timer _Tp;
    public:
        MalachiTeleportPose(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleporting state
class MalachiTeleporting : public GenericState
{
    private:
        Timer _Tp;
    public:
        MalachiTeleporting(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleported state
class MalachiTeleported : public GenericState
{
    private:
        Timer _Tp;
    public:
        MalachiTeleported (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Hurt state
class MalachiHurt : public GenericState
{
    private:

    public:
        MalachiHurt (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};

//Vulnerable state
class MalachiVulnerable : public GenericState
{
    private:

    public:
        MalachiVulnerable (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};

#endif//GAME_MALACHI