#ifndef LICHEN_ENEMY
#define LICHEN_ENEMY

#include "Components/StateMachine.hpp"
#include "Components/StateMachine.hpp"
#include "Components/AARectangle.hpp"
#include "Tools/AStar.hpp"
#include "Tools/Xrand.hpp"

#define ATTACK_TIME 0.8
#define MAX_WANDERING_INTERVAL 20
#define MIN_WANDERING_INTERVAL 8
#define MAX_WANDERING_DISTANCE 600

#define DEFAULT_HP 20
#define DEFAULT_ATTACK_COOLDOWN 3
#define DEFAULT_DETECTION_RANGE 500
#define DEFAULT_ATTACK_RANGE 150
#define DEFAULT_DAMAGE 2
#define DEFAULT_KNOCKBACK_FORCE 3000
#define DEFAULT_MOVIMENTATION_SPEED 100

#define ENEMY_IDLE SMState::Type01
#define ENEMY_WALK SMState::Type02
#define ENEMY_PURSUIT SMState::Type03
#define ENEMY_FIGHTING SMState::Type04
#define ENEMY_ATTACK SMState::Type05


class Enemy : public StateMachine {
    private:
        float _Hp;
        float _AttackCooldown;
        float _DetectionRange;
        float _AttackRange;
        float _Damage;
        float _KnockbackForce;
        float _MovimentationSpeed;

    public:
        Enemy(GameObject& Parent, std::string Label);

        
        void SMStart();
        bool MoveTo(Vector2 Destiny, float Dt);
        
        AARectangle* Collider;

        float GetAttackCooldown();
        float GetDetectionRange();
        float GetAttackRange();
        float GetDamage();
        float GetMovimentationSpeed();
        float GetKnockbackForce();

        void SetAttackCooldown(float AttackCooldown);
        void SetDetectionRange(float DetectionRange);
        void SetAttackRange(float AttackRange);
        void SetDamage(float Damage);
        void SetMovimentationSpeed(float MovimentationSpeed);
        void SetKnockbackForce(float KnockbackForce);

        class Builder{
        private:
            Enemy* _Enemy;

        public:
            Builder(GameObject& Parent, std::string Label);
            ~Builder();
            Builder& SetAttackCooldown(float AttackCooldown);
            Builder& SetDetectionRange(float DetectionRange);
            Builder& SetAttackRange(float AttackRange);
            Builder& SetDamage(float Damage);
            Builder& SetMovimentationSpeed(float MovimentationSpeed);
            Builder& SetKnockbackForce(float KnockbackForce);
            Builder& SetCollider(AARectangle* Collider);
            Builder& AddState(float KnockbackForce);
            Builder& AddSprite(Sprite* Sheet);
            Builder& AddState(SMState Id, GenericState* Add);
            Builder& SetInitialState(SMState Id);
            void Reset();
            Enemy* Build();
        };

};

class EnemyIdle : public GenericState {
    private:
        float _WanderingInterval;
        Timer _WanderingTimer;
        XrandU64 _Randomizer;

    public:
        EnemyIdle(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        
        void GenerateRandomInterval();
};

class EnemyWalk : public GenericState {
    private:
        Vector2 _EnemyDistance;
        XrandU64 _Randomizer;

    public:
        bool Collided;

        EnemyWalk(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
        void OnCollision(StateMachine& Sm, GameObject& Other);

        void GenerateRandomDistance();
};

class EnemyPursuit : public GenericState {
    private:
        std::queue<Vector2> EnemyPath;
    public:
        EnemyPursuit(const StateInfo& Specs);
        void PhysicsUpdate(StateMachine& Sm, float Dt);
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