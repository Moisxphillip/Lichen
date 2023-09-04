#include "../lib/Bullet.hpp"

#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Collider.hpp"

Bullet::Bullet(GameObject& GameObj, float Angle, float Speed, int Damage, 
float MaxDistance, std::string Texture, int Frames, bool Loop, bool TargetsPlayer)
: Component(GameObj)
{
    Sprite* SpBullet = new Sprite(GameObj, Texture, Frames, Frames,1, 0.1, 0);
    SpBullet->Loop = Loop;
    Parent.Box.h = SpBullet->GetHeight();
    Parent.Box.w = SpBullet->GetWidth();
    Collider* CollideBullet = new Collider(GameObj);
	CollideBullet->Box = Parent.Box;
    
    Parent.AddComponent(SpBullet);
    Parent.AddComponent(CollideBullet);

    this->TargetsPlayer = TargetsPlayer;
    
    _Speed = Vector2(1,0)*Speed;
    _Speed.Rotate(Angle);
    Parent.Angle = Angle;
    _DistanceLeft = MaxDistance;
    
    _Damage = Damage;

}

void Bullet::Collided(GameObject& Other)
{
    // Bullet* Shot = (Bullet*) Other.GetComponent("Bullet");
    // if(Shot == nullptr)
    // {
    //     Component* Entity = Other.GetComponent("Alien");
    //     if(Entity != nullptr && !TargetsPlayer)
    //     {
    //         Parent.RequestDelete();
    //         return;
    //     }

    //     Entity = Other.GetComponent("PenguinBody");
    //     if(Entity != nullptr && TargetsPlayer)
    //     {
    //         Parent.RequestDelete();
    //         return;
    //     }
    // }
}

bool Bullet::Is(std::string Type)
{
    return (Type == "Bullet");
}

void Bullet::Render()
{
}

void Bullet::Start()
{
}

void Bullet::Update(float Dt)
{
    Parent.Box+= _Speed*Dt;
    _DistanceLeft -= _Speed.Magnitude()*Dt;
    if(_DistanceLeft <= 0)
    {
        Parent.RequestDelete();
    }

}

int Bullet::GetDamage()
{
    return _Damage;
}