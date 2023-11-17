#ifndef GAME_COMBAT
#define GAME_COMBAT

#include "Tools/Xrand.hpp"
#include <ostream>

struct Stats
{
    int HP, MaxHP, Level, Exp;
    int Vit, Str, Dex, Int;
    friend std::ostream& operator<<(std::ostream& Out, const Stats& stats);
};

enum ScalingStats
{
    NoStats   = 0,
    Vitality  = 1,
    Strength  = 1<<1,
    Dexterity = 1<<2,
    Intelect  = 1<<3,
};

struct AttackData
{
    int BaseDamage;
    ScalingStats Scaled = ScalingStats::NoStats;
};

class Combat
{
    private:
        static XrandU64 Dice;

    public:
        Combat();
        static int Calculate(Stats& Attacker, AttackData& AtkData, Stats& Defender);

};

#endif//GAME_COMBAT