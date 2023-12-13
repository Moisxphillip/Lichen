#include "Enemy/SlimeEnemy.hpp"
#include "Character/Player.hpp"
#include "Core/Engine.hpp"
#include "Definitions.hpp"
#include <iostream>


Slime::Slime(GameObject& Parent, std::string Label , Stats EnemyStats):Enemy(Parent, Label, EnemyStats),_LeapSpeed(30000)
{}

float Slime::GetLeapSpeed()
{
    return _LeapSpeed;
}

void Slime::SetLeapSpeed(float LeapSpeed)
{
    _LeapSpeed = LeapSpeed;
}

void Slime::SMOnCollision(GameObject& Other)
{
    if(_CurrState != ENEMY_HURT && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats, Parent.Box.Center());

        if(MyStats.HP <= 0)
        {
            // SetState(PLAYER_DEATH);
            // GameObject* Drop = new GameObject();
            // Drop->Depth = DepthMode::Dynamic;
            // Drop->AddComponent(new Equipment(*Drop));
            // Drop->Box.SetCenter(Parent.Box.Center());
            // Engine::Instance().CurrentScene().AddGameObj(Drop);
            if(Player::Self != nullptr)
            {
                Player::Self->AddExperience(Combat::DeathExp(MyStats.Level));
            }
            
            Parent.RequestDelete();
            return;
        }

        SetState(ENEMY_HURT);
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}

void Slime::Update(float Dt)
{
    // if (_CurrState == SMState::None)
    // {
    //     return;
    // }
    // SMState Now = _CurrState;
    // _States[_CurrState].get()->Update(*this, Dt);
    // SMUpdate(Dt);
    // for(int i = 0; i<(int)_Sections.size(); i++)
    // {
    //     _Sections[i].get()->Update(Dt);
    // }
    // // if(Now != _CurrState)
    // // {
    // //     Update(Dt);
    // // }
    _Sections[0].get()->
}



// ___________________________________________________________________EnemyAttack___________________________________________________________________

SlimeAttack::SlimeAttack(const StateInfo& Specs):EnemyAttack(Specs), _HasAttacked(false){
    _AttackTimer.Restart();
}

void SlimeAttack::PhysicsUpdate(StateMachine& Sm, float Dt){

    _AttackTimer.Update(Dt);

    Slime* SlimeSM = reinterpret_cast<Slime*>(&Sm);

    if(_AttackTimer.Get()>ATTACK_TIME){
        Sm.SetState(ENEMY_IDLE);
        _AttackTimer.Restart();
        SlimeSM->MyCollider->SetFriction(DEFAULT_FRICTION);
        _HasAttacked = false;
        return;
    }

    

    // if (_AttackTimer.Get() >= SlimeSM->GetAttackTimePoint())
    // {
    //     auto DownDirection = _DirectionLeap.Rotated(M_PI/2).Normalize()*1500;
    //     SlimeSM->MyCollider->ApplyForce(DownDirection) ;
    // }

    if(!_HasAttacked)
    {
        SlimeSM->MyCollider->SetFriction(0.05f);

        _DirectionLeap = Sm.Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center()).Normalized()*100000;
        // auto UpDirection = _DirectionLeap.Rotated(-M_PI/2).Normalize()*1500;

        SlimeSM->MyCollider->ApplyForce(_DirectionLeap) ;
        _HasAttacked = true;
    }


    // setar um vetor speed e subtrair dele até chegar na altura do destiny position
    
}
