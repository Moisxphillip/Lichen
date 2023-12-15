#ifndef LICHEN_ENEMY
#define LICHEN_ENEMY

#include "Components/StateMachine.hpp"
#include "Components/AARectangle.hpp"
#include "Components/AACircle.hpp"
#include "Mechanics/Attack.hpp"
#include "Tools/AStar.hpp"
#include "Tools/Xrand.hpp"

#define ATTACK_TIME 0.8
#define MAX_WANDERING_INTERVAL 20
#define MIN_WANDERING_INTERVAL 8
#define MAX_WANDERING_DISTANCE 600

#define DEFAULT_HP 20
#define DEFAULT_ATTACK_COOLDOWN 3

#define DEFAULT_DAMAGE 2
#define DEFAULT_KNOCKBACK_FORCE 3000
#define DEFAULT_MOVIMENTATION_SPEED 2000
#define DEFAULT_SEARCH_TIME 0.8f

#define DEFAULT_ATTACK_RANGE 100*100
#define DEFAULT_FOLLOW_RANGE 90*90
#define DEFAULT_DETECTION_RANGE 380*380
#define DEFAULT_MEMORY_RANGE 550*550

#define DEFAULT_INVULNERABILITY 0.6f
#define DEFAULT_FRICTION 0.1f


#define ENEMY_IDLE SMState::Type01
#define ENEMY_WALK SMState::Type02
#define ENEMY_PURSUIT SMState::Type03
#define ENEMY_FIGHTING SMState::Type04
#define ENEMY_ATTACK SMState::Type05
#define ENEMY_HURT SMState::Type06
#define ENEMY_DEATH SMState::Type07

#define DEFAULT_STATS Stats{50, 50, 1, 0, 5, 5, 5, 5, 0, 0, 0, 0}


class Enemy : public StateMachine {
    protected:
        Timer _HitCooldown;
        float _FlickTime;
        bool _Flick;

        float _Hp;
        float _AttackCooldown;
        float _DetectionRange;
        float _AttackRange;
        float _Damage;
        float _KnockbackForce;
        float _MovimentationSpeed;
        float _AttackTimePoint;

        float _SearchTime;
        float _FollowRange;
        float _MemoryFollowRange;

    public:
        Stats MyStats;
        AACollider* MyCollider;
        static int EnemyCount;
        static int MaxEnemyCount;

        Enemy(GameObject& Parent, std::string Label = "Enemy", Stats EnemyStats = DEFAULT_STATS);
        
        ~Enemy();

        virtual void SMStart();
        virtual void MoveTo(Vector2 Destiny, float Dt);
        virtual void SMUpdate(float Dt);
        virtual void SMOnCollision(GameObject& Other);
        
        AARectangle* Collider;

        float GetAttackCooldown();
        float GetDetectionRange();
        float GetAttackRange();
        float GetDamage();
        float GetMovimentationSpeed();
        float GetKnockbackForce();
        float GetFlickTime();
        float GetSearchTime();
        float GetFollowRange();
        float GetMemoryFollowRange();
        float GetAttackTimePoint();

        void SetAttackCooldown(float AttackCooldown);
        void SetDetectionRange(float DetectionRange);
        void SetAttackRange(float AttackRange);
        void SetDamage(float Damage);
        void SetMovimentationSpeed(float MovimentationSpeed);
        void SetKnockbackForce(float KnockbackForce);
        void SetFlickTime(float FlickTime);
        void SetSearchTime(float SearchTime);
        void SetFollowRange(float FollowRange);
        void SetMemoryFollowRange(float MemoryFollowRange);
        void SettAttackTimePoint(float AttackTimePoint);
        void PlaySeek();
        void PlayHurt();

        class Builder{
        private:
            Enemy* _Enemy;

        public:
            Builder(GameObject& Parent, std::string Label, Stats EnemyStats = DEFAULT_STATS);
            ~Builder();
            
            Builder& SetAttackCooldown(float AttackCooldown);
            Builder& SetDetectionRange(float DetectionRange);
            Builder& SetAttackRange(float AttackRange);
            Builder& SetRepresentationMask(CollisionMask Represents);
            Builder& SetInteractionMask(CollisionMask Interacts);
            Builder& SetFlickTime(float FlickTime);
            Builder& SetDamage(float Damage);
            Builder& SetMovimentationSpeed(float MovimentationSpeed);
            Builder& SetKnockbackForce(float KnockbackForce);
            Builder& SetCollider(AACollider* Collider);
            Builder& AddState(float KnockbackForce);
            Builder& AddSprite(Sprite* Sheet);
            Builder& AddState(SMState Id, GenericState* Add);
            Builder& SetInitialState(SMState Id);
            Builder& SetSearchTime(float SearchTime);
            Builder& SetFollowRange(float FollowRange);
            Builder& SetMemoryFollowRange(float MemoryFollowRange);
            Builder& SetAttackTimePoint(float AttackTimePoint);

            void Reset();
            Enemy* Build();
        };

};

class EnemyIdle : public GenericState 
{
    public:
        EnemyIdle(const StateInfo& Specs);
        virtual void PhysicsUpdate(StateMachine& Sm, float Dt);
};

class EnemyWalk : public GenericState
 {
    protected:
        bool _HasSetLimit;
        Timer _SearchPath;
        bool _UpdateTime;
        Timer _AttackCooldownTimer;
        std::queue<Vector2> Path;

    public:

        EnemyWalk(const StateInfo& Specs);
        virtual void Start();
        virtual void PhysicsUpdate(StateMachine& Sm, float Dt);
        virtual void Update(StateMachine& Sm, float Dt);
};


class EnemyHurt : public GenericState
{
    protected:
        Timer _HurtTime;
    public:
        EnemyHurt(const StateInfo& Specs);
        virtual void Start();
        virtual void Update(StateMachine& Sm, float Dt);
};

class EnemyDeath: public GenericState
{
    protected:
        Timer _HurtTime;
    public:
        EnemyDeath(const StateInfo& Specs);
        virtual void Start();
        virtual void Update(StateMachine& Sm, float Dt);
};

class EnemyAttack : public GenericState {
    protected:
        Timer _AttackTimer;
        bool _HasAttacked;
    public:
        EnemyAttack(const StateInfo& Specs);
        virtual void PhysicsUpdate(StateMachine& Sm, float Dt);
};



#endif