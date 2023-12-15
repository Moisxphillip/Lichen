#ifndef GAME_PROGRESS
#define GAME_PROGRESS

#include "Mechanics/Combat.hpp"

class Progress
{
    public:
        static Stats PlayerStats;
        static bool ShouldReset;
        static void ResetGame();
        static bool TookQuest1;
        static bool DestroyedSpawns;
        static bool DefeatedBoss1;
        static bool TookQuest2;
        static bool DestroyedBarrier;
        static bool DisableSpawn;
        static bool KillMinions;
        static bool DefeatedBoss2;
        static bool TookQuest3;
};

#endif//GAME_PROGRESS