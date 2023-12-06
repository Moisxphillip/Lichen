#ifndef GAME_SPAWNER
#define GAME_SPAWNER

#include <functional>

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"

class Spawner : public Component
{
     private:
        Timer _ToSpawn;
        float _MinRadius;
        float _MaxRadius;
        float _Spread;
    public:
        Spawner(GameObject& Parent, float Time, float MinDist, float MaxDist, float SpawnRadius, bool DeleteAfter);
        void Update(float Dt);
};

Spawner::Spawner(GameObject& Parent, float Time, float MinDist, float MaxDist, float SpawnRadius, bool DeleteAfter)
: Component(Parent)
{

}
#include "Npc/Critter.hpp"
#include "Core/Engine.hpp"
void Spawner::Update(float Dt)
{
    _ToSpawn.Update(Dt);
    if(_ToSpawn.Finished())
    {
        //TODO set rules and creatures to spawn
        GameObject* Obj = new GameObject();
        Obj->AddComponent(new Bird(*Obj));
        Obj->Box.SetPosition(Parent.Box.Center() 
            + Vector2(_Spread * Engine::RandomFloat(),0.0f).Rotated(M_PI*2*Engine::RandomFloat()));
        Engine::Instance().CurrentScene().AddGameObj(Obj);

        Obj = new GameObject();
        Obj->AddComponent(new Worm(*Obj));
        Obj->Box.SetPosition(Parent.Box.Position() 
            + Vector2(_Spread * Engine::RandomFloat(),0.0f).Rotated(M_PI*2*Engine::RandomFloat()));
        Engine::Instance().CurrentScene().AddGameObj(Obj);
        _ToSpawn.Restart();
    }


}



#endif//GAME_SPAWNER