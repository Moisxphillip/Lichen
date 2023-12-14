#include "Mechanics/Progress.hpp"

bool Progress::TookQuest1       = false;
bool Progress::DestroyedSpawns  = false;
bool Progress::DefeatedBoss1    = false;
bool Progress::TookQuest2       = false;
bool Progress::DestroyedBarrier = false;
bool Progress::DisableSpawn    = false;
bool Progress::KillMinions      = false;
bool Progress::DefeatedBoss2    = false;
bool Progress::TookQuest3       = false;

void Progress::ResetGame()
{
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
