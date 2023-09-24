#include "Tools/Timer.hpp"

Timer::Timer()
{
    _Time = 0;
}

float Timer::Get()
{
    return _Time;
}

void Timer::Restart()
{
    _Time = 0;
}

void Timer::Update(float Dt)
{
    _Time += Dt;
}