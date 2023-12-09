#ifndef GAME_PROJECTILE
#define GAME_PROJECTILE

#include "Components/Component.hpp"
#include "Definitions.hpp"
#include "Components/AACircle.hpp"

class Projectile : public Component
{
    private:
        // Vector2 _Velocity;
        bool _Die;
        AACircle* _Collider;
    public:
        Projectile(GameObject& Parent, Vector2 Velocity, float Ray, CollisionMask Interacts);
        void Start();
        void Update(float Dt);
        void OnCollision(GameObject& Other);
};

#endif//GAME_PROJECTILE
