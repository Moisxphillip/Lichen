// #ifndef GAME_SLIME
// #define GAME_SLIME

// #include "Components/StateMachine.hpp"
// #include "Components/AACircle.hpp"
// #include "Math/Vector2.hpp"
// #include "Mechanics/Attack.hpp"

// #include <queue>

// //The core entity
// class Slime : public StateMachine
// {
//     private:
//         Timer _HitCooldown;
//         float _FlickTime;
//         bool _Flick;
        
//     public:
//         static int EnemyCount;
//         Stats MyStats;
//         AACircle* MyCollider;
//         Slime(GameObject& Parent, std::string Label = "Slime");
//         ~Slime();
//         void MoveTo(Vector2 Destiny, float Dt);
//         void SMStart();
//         void SMUpdate(float Dt);
//         void SMOnCollision(GameObject& Other);
//         Vector2 Target;
// };

// //Idle state
// class SlimeIdle : public GenericState
// {
//     private:

//     public:
//     SlimeIdle(const StateInfo& Specs);
//     void PhysicsUpdate(StateMachine& Sm, float Dt);
// };

// //Walk state
// class SlimeWalk : public GenericState
// {
//     private:
//         Timer _SearchPath;
//         bool _UpdateTime;
//         std::queue<Vector2> Path;
//     public:
//         SlimeWalk(const StateInfo& Specs);
//         void Start();
//         void PhysicsUpdate(StateMachine& Sm, float Dt);
//         void Update(StateMachine& Sm, float Dt);
// };

// //Hurt state
// class SlimeHurt : public GenericState
// {
//     private:
//         Timer _HurtTime;
//     public:
//         SlimeHurt(const StateInfo& Specs);
//         void Start();
//         void Update(StateMachine& Sm, float Dt);
// };
// #endif//GAME_SLIME