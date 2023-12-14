#ifndef GAME_SPAWNER
#define GAME_SPAWNER

#include <functional>
#include <vector>

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Enemy/EnemyFactory.hpp"
#include "Character/Player.hpp"

class Spawner : public Component
{
     private:
        Timer _ToSpawn;
        float _MinRadius;
        float _MaxRadius;
        float _Spread;
        int _MinLvl, _MaxLvl;
        int _ChooseLvl(int PlayerLvl, int MinLvl, int MaxLvl, float Rng);
        std::vector<EnemyType> _Types;

    public:
        // Spawner(GameObject& Parent, float Time, float MinDist, float MaxDist, float SpawnRadius, bool DeleteAfter);
        Spawner(GameObject& Parent, 
            float Time, float MinDist, float MaxDist,
            int MinLvl, int MaxLvl, float SpawnRadius,
            std::vector<EnemyType> Types);

        void Update(float Dt);
};


//TODO FINISH!!!!
Spawner::Spawner(GameObject& Parent, float Time, float MinDist, float MaxDist,
            int MinLvl, int MaxLvl, float SpawnRadius, std::vector<EnemyType> Types);
: Component(Parent), _MinDist(MinDist), _MaxDist(MaxDist), _MinRadius(MinDist), _MaxRadius(MaxDist)
{
    _Types = Types;
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
    if(Progress::DisableSpawn)
    {
        return;
    }
    
    _ToSpawn.Update(Dt);
    if(_ToSpawn.Finished() && Player::Self != nullptr)//TODO check distances and spawn mode also
    {
        EnemyType Tp = _Types[Engine::RandomUint()%_Types.size()];
        int Lvl = _ChooseLvl(Player::Self->GetStats().Level, );
        // //TODO set rules and creatures to spawn
        // GameObject* Obj = new GameObject();
        // Obj->AddComponent(new Bird(*Obj));
        // Obj->Box.SetPosition(Parent.Box.Center() 
        //     + Vector2(_Spread * Engine::RandomFloat(),0.0f).Rotated(M_PI*2*Engine::RandomFloat()));
        // Engine::Instance().CurrentScene().AddGameObj(Obj);

        // Obj = new GameObject();
        // Obj->AddComponent(new Worm(*Obj));
        // Obj->Box.SetPosition(Parent.Box.Position() 
        //     + Vector2(_Spread * Engine::RandomFloat(),0.0f).Rotated(M_PI*2*Engine::RandomFloat()));
        // Engine::Instance().CurrentScene().AddGameObj(Obj);
        _ToSpawn.Restart();
    }


}



#endif//GAME_SPAWNER