#ifndef GAME_FITZGERALD
#define GAME_FITZGERALD

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"
#include "Mechanics/Combat.hpp"

class FitzGerald : public StateMachine
{
    private:
        Timer _HitCooldown;
        float _FlickTime;
        bool _Flick;
        
    public:
        SMState NextState;
        FitzGerald(GameObject& Parent, std::string Label = "FitzGerald");

        static FitzGerald* Self;
        GameObject* Arena[5];
        Stats MyStats;
        AACircle* MyCollider;
        int AttackPattern;
        int RemainingAttacks;
        void SetAddColor(Color Color);
        void SetScale(Vector2 Scale);
        
        
        ~FitzGerald();
        void SMStart();
        void SMUpdate(float Dt);
        void SMOnCollision(GameObject& Other);
        void SetupArena();
        void MoveTo(Vector2 Destiny, float Dt);
};

//Idle state
class FitzGeraldIdle : public GenericState
{
    private:
        bool _Started;
        Timer _AttackDelay;
        Timer _ChangeState;
        int _TeleportChance, _ShootChance;
    public:
        void Start();
        FitzGeraldIdle(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};


//Punch Atack down
class FitzGeraldPunchDown : public GenericState
{
    private:
        bool _HasAttacked;
        Timer _AtkTime;
    public:
        FitzGeraldPunchDown(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Swipe Atack down
class FitzGeraldSwipeDown : public GenericState
{
    private:
        bool _HasAttacked;
        Timer _AtkTime;
    public:
        FitzGeraldSwipeDown(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};



class FitzGeraldHorizontalPunch : public GenericState
{
    private:
        bool _HasAttacked;
        Timer _AtkTime;
    public:
        FitzGeraldHorizontalPunch(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Pose state
class FitzGeraldTeleportPose : public GenericState
{


    private:
        bool _Started;
        Timer _Tp;
    public:
        FitzGeraldTeleportPose(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleporting state
class FitzGeraldTeleporting : public GenericState
{
    private:
        Timer _Tp;
    public:
        FitzGeraldTeleporting(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Teleported state
class FitzGeraldTeleported : public GenericState
{
    private:
        Timer _Tp;
    public:
        FitzGeraldTeleported (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Hurt state
class FitzGeraldHurt : public GenericState
{
    private:
        Timer _HurtTime;
    public:
        FitzGeraldHurt (const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);
};


#endif//GAME_MALACHI