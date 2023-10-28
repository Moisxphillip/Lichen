#include "Tools/Timer.hpp"

Timer::Timer(float TimeLimit)
: _Limit(TimeLimit)
{
    _Time = 0.0f;
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

bool Timer::Finished()
{
    return _Time > _Limit;
}

void Timer::SetLimit(float TimeLimit)
{
    _Limit = TimeLimit;
}