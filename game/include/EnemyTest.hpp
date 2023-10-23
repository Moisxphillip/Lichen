// #ifndef LICHEN_EnemyTest
// #define LICHEN_EnemyTest

// #include "Components/StateMachine.hpp"
// #include "Components/AARectangle.hpp"
// #include "Tools/AStar.hpp"

// class EnemyTest : public StateMachine {
//     private:
//         int _Hp;
//         // int _AttackCooldown;
//         float _DetectionDistance;
//         float _AttackDistance;

//     public:
//         EnemyTest(GameObject& Parent, std::string Label="EnemyTest", float DetectionDistance = 400, float AttackDistance = 200);
//         AARectangle* EnemyTestCollider;
//         void SMStart();
//         float GetDetectionDistance();
//         float GetAttackDistance();
//         int GetAttackCooldown();
//         void SetDetectionDistance(float Distance);
//         Vector2 LastPlayerQuadrant;
//         std::queue<Point> EnemyTestPath;

// };

// class EnemyTestIdle : public GenericState {
//     private:
//     public:
//         EnemyTestIdle(const StateInfo& Specs);
//         void PhysicsUpdate(StateMachine& Sm, float Dt);
//         void Update(StateMachine& Sm, float Dt);
// };

// class EnemyTestWalk : public GenericState {
//     private:
//     public:
//         EnemyTestWalk(const StateInfo& Specs);
//         void PhysicsUpdate(StateMachine& Sm, float Dt);
// };

// class EnemyTestAttack : public GenericState {
//     private:
//         Timer _AttackCooldownTimer;
//     public:
//         EnemyTestAttack(const StateInfo& Specs);
//         void Attack();
//         void PhysicsUpdate(StateMachine& Sm, float Dt);
// };

// #endif
