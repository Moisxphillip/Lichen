#ifndef GAME_COMBAT
#define GAME_COMBAT

#include "Tools/Xrand.hpp"
#include <ostream>

struct Stats
{
    int HP, MaxHP, Level, Exp;
    int Vit, Str, Dex, Int;
    int Stamina=0, MaxStamina=0, Mana=0, MaxMana=0;
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
    unsigned int Knockback = 1;
    ScalingStats Scaled = ScalingStats::NoStats;
};

class Combat
{
    private:
        static XrandU64 Dice;
        static int _DamagePenalty(int AttackerLevel, int TargetLevel, float Damage);

    public:
        Combat();
        static int CalculateDamage(Stats& Attacker, AttackData& AtkData, Stats& Defender);
        static int DeathExp(int CurrentLevel);
        static int LevelUpExp(int CurrentLevel);
};

#endif//GAME_COMBAT