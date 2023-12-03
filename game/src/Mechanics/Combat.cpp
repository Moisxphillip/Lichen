#include "Mechanics/Combat.hpp"

#include <cmath>
#include <ctime>

XrandU64 Combat::Dice;

Combat::Combat()
{
    Dice.seed(static_cast<unsigned long long int>(std::time(nullptr)));
}

int Combat::CalculateDamage(Stats& Attacker, AttackData& AtkData, Stats& Defender)
{
    float Damage = AtkData.BaseDamage, Accumulator = 0.0f;

    Accumulator += (AtkData.Scaled | ScalingStats::Strength  ? Damage * ((float)Attacker.Str/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Dexterity ? Damage * ((float)Attacker.Dex/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Intelect  ? Damage * ((float)Attacker.Int/100.0f) : 0.0f);

    Damage+=Accumulator;
    int Roll =  Dice.gen()%20 + 1;
    Damage = (Roll == 20 ? Damage*1.5f : (Roll == 1 ? Damage*0.75f : Damage)); //Crit & fail
    int FinalDamage = _DamagePenalty(Attacker.Level, Defender.Level, Damage) - (Defender.Vit/10.0f);

    Defender.HP -= FinalDamage;
    return FinalDamage;
}

int Combat::_DamagePenalty(int AttackerLevel, int TargetLevel, float Damage)
{
    int LevelDiff = AttackerLevel - TargetLevel;
    if(LevelDiff >= 0)
    {
        return Damage;
    }
    float FinalDmg = std::max(std::pow(LevelDiff*0.04f, 3.0f) + 5.0f, 1.0f);
    return std::round(FinalDmg);
}

int Combat::DeathExp(int CurrentLevel)
{
    return std::round(0.05*std::pow(CurrentLevel, 2) + CurrentLevel*1.2 + 1);
}

int Combat::LevelUpExp(int CurrentLevel)
{
    return std::round(0.03f * std::pow(CurrentLevel, 3) + std::pow(CurrentLevel, 2) + 2 * CurrentLevel + CurrentLevel);
}

std::ostream& operator<<(std::ostream& Out, const Stats& stats)
{
    Out << "Stats:\nHP: " << stats.HP << "\nMax HP: " << stats.MaxHP 
        << "\nLevel: " << stats.Level << "\nExp: " << stats.Exp
        << "\nVit: " << stats.Vit << "\nStr: " << stats.Str
        << "\nDex: " << stats.Dex << "\nInt: " << stats.Int;
    return Out;
}
