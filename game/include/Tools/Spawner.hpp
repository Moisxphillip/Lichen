#ifndef GAME_SPAWNER
#define GAME_SPAWNER

#include <functional>
#include <vector>

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Enemy/EnemyFactory.hpp"


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
            std::vector<EnemyType> Types, bool Destructable = false);

        void Update(float Dt);
};

class PunchBag : public Component
{
    private:
        Stats _Stats;
        Timer _Invulnerable;
    public:
        static int SpawnerCount;
        PunchBag(GameObject& Parent, int HP = 10);
        ~PunchBag();
        void Start();
        void OnCollision(GameObject& Other);
        void Update(float Dt);
};

#endif//GAME_SPAWNER