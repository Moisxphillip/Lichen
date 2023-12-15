#include "Mechanics/Progress.hpp"

Stats Progress::PlayerStats = Stats{100, 100, 1, 0, 5, 5, 5, 5, 3, 3, 100, 100};
bool Progress::ShouldReset      = true;
bool Progress::TookQuest1       = false;
bool Progress::DestroyedSpawns  = false;
bool Progress::DefeatedBoss1    = false;
bool Progress::TookQuest2       = false;
bool Progress::DestroyedBarrier = false;
bool Progress::DisableSpawn     = false;
bool Progress::KillMinions      = false;
bool Progress::DefeatedBoss2    = false;
bool Progress::TookQuest3       = false;

void Progress::ResetGame()
{
    PlayerStats = Stats{100, 100, 1, 0, 5, 5, 5, 5, 3, 3, 100, 100};
    TookQuest1       = false;
    DestroyedSpawns  = false;
    DefeatedBoss1    = false;
    TookQuest2       = false;
    DestroyedBarrier = false;
    DisableSpawn    = false;
    KillMinions      = false;
    DefeatedBoss2    = false;
    TookQuest3       = false;
}
