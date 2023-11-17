#include "Mechanics/Attack.hpp"
#include "Definitions.hpp"

Attack::Attack(GameObject& Parent, Stats& Attacker, AttackData Data, CollisionMask Target, float LifeTime, float AfterHitLifeTime)
: Component(Parent), Attacker(Attacker), Data(Data), _LifeTime(LifeTime), _AfterHitLifeTime(AfterHitLifeTime)
{
    _Type = COMPONENT_ATTACK;
    Parent.Interacts = Parent.Interacts | Target;
    LifeTime == 0.0f ? _SelfDestruct = false : _SelfDestruct = true;
    AfterHitLifeTime == 0.0f ? _HitDestruct = false : _HitDestruct = true;
}

void Attack::Update(float Dt)
{
    if(!_SelfDestruct)
    {
        return;
    }
    
    _LifeTime.Update(Dt);
    if(_LifeTime.Finished())
    {
        Parent.RequestDelete();
    }
}

void Attack::OnCollision(GameObject& Other)
{
    if(!_HitDestruct)
    {
        return;
    }
    _LifeTime.SetLimit(_AfterHitLifeTime);
    _LifeTime.Restart();
    _HitDestruct = false; //to avoid resetting for every hit
    _SelfDestruct = true; //in case it wasn't self-destructive before
}

//Attack assumes you have a collider on its gameobject, otherwise it will not work