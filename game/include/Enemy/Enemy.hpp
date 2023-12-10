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
#define DEFAULT_DETECTION_RANGE 380*380
#define DEFAULT_ATTACK_RANGE 150
#define DEFAULT_DAMAGE 2
#define DEFAULT_KNOCKBACK_FORCE 3000
#define DEFAULT_MOVIMENTATION_SPEED 2000
#define DEFAULT_SEARCH_TIME 0.8f
#define DEFAULT_FOLLOW_RANGE 80*80
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
    private:
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

        float _SearchTime;
        float _FollowRange;
        float _MemoryFollowRange;

    public:
        Stats MyStats;
        AACollider* MyCollider;
        static int EnemyCount;

        Enemy(GameObject& Parent, std::string Label = "Enemy", Stats EnemyStats = DEFAULT_STATS);
        
        ~Enemy();

        void SMStart();
        void MoveTo(Vector2 Destiny, float Dt);
        void SMUpdate(float Dt);
        void SMOnCollision(GameObject& Other);
        
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

            void Reset();
            Enemy* Build();
        };

};

class EnemyIdle : public GenericState 
{
    public:
        EnemyIdle(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
};

class EnemyWalk : public GenericState
 {
    private:
        bool _HasSetLimit;
        Timer _SearchPath;
        bool _UpdateTime;
        std::queue<Vector2> Path;

    public:

        EnemyWalk(const StateInfo& Specs);
        void Start();
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void Update(StateMachine& Sm, float Dt);
};


class EnemyHurt : public GenericState
{
    private:
        Timer _HurtTime;
    public:
        EnemyHurt(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

class EnemyDeath: public GenericState
{
    private:
        Timer _HurtTime;
    public:
        EnemyDeath(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

class EnemyFighting : public GenericState {
    private:
        Timer _AttackCooldownTimer;
    public:
        EnemyFighting(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};

class EnemyAttack : public GenericState {
    private:
        Timer _AttackTimer;
    public:
        EnemyAttack(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
};

#endif