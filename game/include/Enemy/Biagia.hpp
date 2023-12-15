#ifndef GAME_BIAGIA
#define GAME_BIAGIA

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Mechanics/Combat.hpp"

class Biagia : public StateMachine
{
    private:
        Timer _HitCooldown;
        float _FlickTime;
        bool _Flick;
        
    public:
        int Summons;
        static Biagia* Self;
        GameObject* Arena[5];
        Sprite* Shield;
        Stats MyStats;
        AACircle* MyCollider;
        Biagia(GameObject& Parent, std::string Label = "Biagia");
        ~Biagia();
        void SMStart();
        void SMUpdate(float Dt);
        void SMOnCollision(GameObject& Other);
        void SetupArena();
        void Spawn();
};

//Idle state
class BiagiaIdle : public GenericState
{
    private:
        Timer _ChangeState;
        int _TeleportChance, _ShootChance;
    public:
        void Start();
        BiagiaIdle(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};


//Spawn enemy
class BiagiaSpawn : public GenericState
{
    private:
        Timer _AtkTime;
    public:
        BiagiaSpawn(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};


//Pose state
class BiagiaTeleportPose : public GenericState
{
    private:
        Timer _Tp;
    public:
        BiagiaTeleportPose(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleporting state
class BiagiaTeleporting : public GenericState
{
    private:
        Timer _Tp;
    public:
        BiagiaTeleporting(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleported state
class BiagiaTeleported : public GenericState
{
    private:
        Timer _Tp;
    public:
        BiagiaTeleported (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Hurt state
class BiagiaHurt : public GenericState
{
    private:

    public:
        BiagiaHurt (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};

//Vulnerable state
class BiagiaVulnerable : public GenericState
{
    private:
        Timer _VulnerableTime;
    public:
        BiagiaVulnerable (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

#endif//GAME_BIAGIA