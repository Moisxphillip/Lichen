#include "Enemy/Projectile.hpp"
#include "Enemy/Malachi.hpp"

Projectile::Projectile(GameObject& Parent, Vector2 Velocity, float Ray, CollisionMask Interacts)
: Component(Parent), _Die(false)
{
    _Collider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, Ray));
    Parent.AddComponent(_Collider);
    _Collider->SetFriction(0);
    _Collider->Velocity = Velocity;
    Parent.Interacts = Interacts | CollisionMask::Terrain;
}

void Projectile::Start()
{
}

void Projectile::Update(float Dt)
{
    if(_Die)
    {
        Parent.RequestDelete();
    }
}
#include <iostream>
#include <bitset>
void Projectile::OnCollision(GameObject& Other)
{
    if(static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Parent.Represents = REFLECTED_BULLET_MASK;
        Parent.Interacts = PLAYER_MASK | ENEMY_MASK | CollisionMask::Terrain;
        if(Malachi::Self != nullptr)
        {
            float Spd = _Collider->Velocity.Magnitude();
            _Collider->Velocity = Parent.Box.Center().DistVector2(Malachi::Self->Parent.Box.Center()).Normalized()*Spd;
        }
        return;
    }
    // std::cout << std::bitset<32>(static_cast<int>(Other.Represents)) << ' ' << std::bitset<32>(static_cast<int>(Other.Interacts)) << '\n';
    // std::cout << std::bitset<32>(static_cast<int>(Parent.Represents)) << ' ' << std::bitset<32>(static_cast<int>(Parent.Interacts)) << '\n';
    // // else if(static_cast<bool>(Other.Represents & CollisionMask::Terrain))
    // // {
    _Die = true;
    // }
}