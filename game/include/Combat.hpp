#ifndef GAME_COMBAT
#define GAME_COMBAT

#include "Tools/Xrand.hpp"

struct Stats
{
    int HP, MaxHP, Level, Exp;
    int Vit, Str, Dex, Int;
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

Combat::Combat()
{
    Dice.seed(42);//Seed with time later
    Dice.range(1, 20);//D20
}

int Combat::Calculate(Stats& Attacker, AttackData& AtkData, Stats& Defender)
{
    float Damage = AtkData.BaseDamage, Accumulator = 0.0f;

    Accumulator += (AtkData.Scaled | ScalingStats::Strength  ? Damage * ((float)Attacker.Str/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Dexterity ? Damage * ((float)Attacker.Dex/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Intelect  ? Damage * ((float)Attacker.Int/100.0f) : 0.0f);

    int LevelDiff = Defender.Level - Attacker.Level;

    if(LevelDiff < 0) //1 Damage if attacker level is inferior to defender. Must be redone with a decent formula later
    {
        Defender.HP-=1;
        return 1;
    }

    Damage+=Accumulator;
    int Roll =  Dice.gen();
    Damage = (Roll == 20 ? Damage*1.5f : (Roll == 1 ? Damage*0.75f : Damage)); //Crit & fail

    int FinalDamage = Damage - (Defender.Vit/10.0f);
    Defender.HP -= FinalDamage;

    return FinalDamage;
}

#endif//GAME_COMBAT