#ifndef GAME_MOVER
#define GAME_MOVER

#include "Components/Component.hpp"

class SimpleMovement : public Component
{
    private:
        Vector2 _Velocity;
    public: 
        SimpleMovement(GameObject& Parent, Vector2 Velocity);
        void SetMovement(Vector2 Velocity);
        Vector2 GetMovement();
        void PhysicsUpdate(float Dt);
};

#endif//GAME_MOVER