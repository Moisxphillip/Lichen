#include "Mechanics/Combat.hpp"

XrandU64 Combat::Dice;

Combat::Combat()
{
    Dice.seed(42);//Seed with time later
    // Dice.range(1, 20);//D20 //BUG Range is not working here, use mod
}

int Combat::Calculate(Stats& Attacker, AttackData& AtkData, Stats& Defender)
{
    float Damage = AtkData.BaseDamage, Accumulator = 0.0f;

    Accumulator += (AtkData.Scaled | ScalingStats::Strength  ? Damage * ((float)Attacker.Str/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Dexterity ? Damage * ((float)Attacker.Dex/100.0f) : 0.0f);
    Accumulator += (AtkData.Scaled | ScalingStats::Intelect  ? Damage * ((float)Attacker.Int/100.0f) : 0.0f);

    int LevelDiff = Defender.Level - Attacker.Level;

    Damage+=Accumulator;
    int Roll =  Dice.gen()%20 + 1;
    Damage = (Roll == 20 ? Damage*1.5f : (Roll == 1 ? Damage*0.75f : Damage)); //Crit & fail

    int FinalDamage = Damage - (Defender.Vit/10.0f);

    if(LevelDiff > 0) //Must be redone with a decent formula later
    {
        FinalDamage = FinalDamage/(LevelDiff*2.0f);
    }

    Defender.HP -= FinalDamage;
    return FinalDamage;
}

std::ostream& operator<<(std::ostream& Out, const Stats& stats)
{
    Out << "Stats:\nHP: " << stats.HP << "\nMax HP: " << stats.MaxHP 
        << "\nLevel: " << stats.Level << "\nExp: " << stats.Exp
        << "\nVit: " << stats.Vit << "\nStr: " << stats.Str
        << "\nDex: " << stats.Dex << "\nInt: " << stats.Int;
    return Out;
}
