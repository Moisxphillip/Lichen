#include "Enemy/Malachi.hpp"
#include "Enemy/Projectile.hpp"

Projectile::Projectile(GameObject& Parent, Vector2 Velocity, float Ray, CollisionMask Interacts)
: Component(Parent), _Die(false)
{
    _Collider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, Ray));
    Parent.AddComponent(_Collider);
    _Collider->SetFriction(0);
    _Collider->Velocity = Velocity;
    Parent.Interacts = Interacts;
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

void Projectile::OnCollision(GameObject& Other)
{
    if(static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Parent.Interacts = (Parent.Interacts ^ PLAYER_MASK) | ENEMY_MASK;
        if(Malachi::Self != nullptr)
        {
            float Spd = _Collider->Velocity.Magnitude();
            _Collider->Velocity = Parent.Box.Center().DistVector2(Malachi::Self->Parent.Box.Center()).Normalized()*Spd;
        }
    }
    else if(!_Die)
    {
        _Die = true;
    }
}

