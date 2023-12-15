#include "Tools/Spawner.hpp"


#include "Definitions.hpp"
#include "Components/AACircle.hpp"


#define INVULN 1.0f

int PunchBag::SpawnerCount = 0;

PunchBag::PunchBag(GameObject& Parent, int HP)
: Component(Parent)
{
    Parent.Represents = CollisionMask::Terrain;
    Parent.Interacts = PLAYER_ATK_MASK;
    _Stats = Stats{HP, HP, 30, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    _Invulnerable.SetLimit(INVULN);
    _Invulnerable.Update(INVULN);
    SpawnerCount++;
}

PunchBag::~PunchBag()
{
    SpawnerCount--;
}

void PunchBag::Start()
{
    Parent.AddComponent(new AACircle(Parent, ColliderKind::Stationary, Circle(0,0,Parent.Box.w/2)));
}

void PunchBag::OnCollision(GameObject& Other)
{
    if(_Invulnerable.Finished() && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, _Stats, Parent.Box.Center());
        if(_Stats.HP <= 0)
        {
            Parent.RequestDelete();
        } 
        _Invulnerable.Restart();
    } 
}

void PunchBag::Update(float Dt)
{
    if(_Invulnerable.Finished())
    {
        return;
    }
    _Invulnerable.Update(Dt);
}


#include "Character/Player.hpp"
#include "Components/Sprite.hpp"

Spawner::Spawner(GameObject& Parent, float Time, float MinDist, float MaxDist,
            int MinLvl, int MaxLvl, float SpawnRadius, std::vector<EnemyType> Types, bool Destructable)
: Component(Parent), _MinLvl(MinLvl), _MaxLvl(MaxLvl), _MinRadius(MinDist*MinDist), _MaxRadius(MaxDist*MaxDist)
{
    _ToSpawn.SetLimit(Time);
    _Spread = SpawnRadius;
    _Types = Types;
    if(Destructable)
    {
        Sprite* Spr = new Sprite(Parent, "./res/img/prop/mobden.png", 9, 9, 1, 0.1f);
        Parent.AddComponent(Spr);
        Parent.Box.Redimension(Vector2(Spr->GetWidth(), Spr->GetHeight()));
        Parent.AddComponent(new PunchBag(Parent, 15));
    }
}
#include "Npc/Critter.hpp"
#include "Core/Engine.hpp"
#include "Mechanics/Progress.hpp"


int Spawner::_ChooseLvl(int PlayerLvl, int MinLvl, int MaxLvl, float Rng)
{
    if(MinLvl>MaxLvl)
    {
        std::swap(MinLvl, MaxLvl);
    }
    PlayerLvl = std::clamp(PlayerLvl, MinLvl, MaxLvl-1);
    float Dist[MaxLvl-MinLvl] = {}, Chance = 0.5f;
    
    for(int i = 0; i< MaxLvl-MinLvl; i++)
    {
        Dist[i] = Chance;
        Chance*=0.3f;//Lower here to increase probability of enemies closer to level
    }
    float Sum = 0;
    float Prob[MaxLvl-MinLvl]={};
    
    for(int i = 0; i<MaxLvl-MinLvl; i++)
    {
        Prob[i] = Dist[std::abs((MinLvl+i) - PlayerLvl)];
        Sum+=Prob[i];
    }
    for(int i = 0; i<MaxLvl-MinLvl; i++)
    {
        Prob[i]/=Sum;
    }
    Sum = 0;
    for(int i = 0; i<MaxLvl-MinLvl; i++)
    {
        Sum+=Prob[i];
        if(Rng < Sum)
        {
            return MinLvl+i;
        }
    }
    return PlayerLvl;
}

void Spawner::Update(float Dt)
{
    if(Progress::DisableSpawn || Player::Self == nullptr || Enemy::EnemyCount >= Enemy::MaxEnemyCount)
    {
        return;
    }
    
    float Distsq = Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center());
    if(Distsq < _MinRadius || Distsq > _MaxRadius)
    {
        return;
    }

    _ToSpawn.Update(Dt);
    if(!_ToSpawn.Finished())
    {
        return;
    }

    EnemyType Tp = _Types[Engine::RandomUint()%_Types.size()];
    int Lvl = _ChooseLvl(Player::Self->GetStats().Level, _MinLvl, _MaxLvl, Engine::RandomFloat());
    GameObject* Go = new GameObject();
    Stats EnStats = {Stats{50+Lvl, 50+Lvl, Lvl, 0, 5+Lvl, 5+Lvl, 5+Lvl, 5+Lvl, 0, 0, 0, 0}};
    Vector2 Position(_Spread * Engine::RandomFloat(), 0.0f);
    Position.Rotate(M_PI*2*Engine::RandomFloat());
    Position+=Parent.Box.Center();
    Go->AddComponent(EnemyFactory::CreateEnemy(*Go, Tp, Position, EnStats));
    Engine::Instance().CurrentScene().AddGameObj(Go);
    _ToSpawn.Restart();

}

//     int HP, MaxHP, Level, Exp;
//     int Vit, Str, Dex, Int;
//     int Stamina=0, MaxStamina=0, Mana=0, MaxMana=0;
