#include "Tools/Tools.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>
// #include "SDL2/SDL.h"

void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    // std::cout << SDL_GetError() << ".\n";
    //call exit(-1) on error?
}

int Fps(int Rate) //Takes intended frames per second and returns approximated time of each frame in ms
{
    return 1000/Rate;
}

template <typename T>
T WrapMax(T Value, T Max)
{
    return std::fmod(Max + std::fmod(Value, Max), Max);
}
template float WrapMax(float Value, float Max);
template double WrapMax(double Value, double Max);


template <typename T>
T WrapMinMax(T Value, T Min, T Max)
{
    return Min + WrapMax(Value - Min, Max - Min);
}
template float WrapMinMax(float Value, float Min, float Max);
template double WrapMinMax(double Value, double Min, double Max);

template <typename T>
T Clamp(T Value)
{
    return (Value < T(0) ? T(0) : (Value > T(1) ? T(1) : Value));
}
template float Clamp(float Value);
template double Clamp(double Value);

template <typename T>
T SmootherStep(T Value, T LowerBound, T HigherBound)
{
    T ClampedValue = Clamp((Value - LowerBound) / (HigherBound - LowerBound));
    return ClampedValue * ClampedValue * ClampedValue * (ClampedValue * (ClampedValue * (T(6) * ClampedValue - T(15)) + T(10)));
}
template float SmootherStep(float Value, float Min, float Max);
template double SmootherStep(double Value, double Min, double Max);

template <typename T>
T SmoothStep(T Value, T LowerBound, T HigherBound)
{
    T ClampedValue = Clamp((Value - LowerBound) / (HigherBound - LowerBound));
    return ClampedValue * ClampedValue * (T(3) - T(2) * ClampedValue);
}
template float SmoothStep(float Value, float Min, float Max);
template double SmoothStep(double Value, double Min, double Max);

template <typename T>
T Attenuation(T Value, T GrowthEnd, T DecreasePoint)
{
    T ClampedValue = Clamp(Value);
    if(ClampedValue < GrowthEnd)
    {
        return SmoothStep(ClampedValue, T(0.0), GrowthEnd);
    }
    else if(ClampedValue > DecreasePoint)
    {
        return SmoothStep(ClampedValue, T(1.0), DecreasePoint);
    }
    return T(1.0);
}
template float Attenuation(float Value, float GrowthEnd, float DecreasePoint);
template double Attenuation(double Value, double GrowthEnd, double DecreasePoint);

template <typename T>
T Lerp(const T& Start, const T& End, float F) 
{
    F = std::clamp(F, 0.0f, 1.0f);
    return Start + F * (End - Start);
}
template float Lerp(const float& Start, const float& End, float F);
template double Lerp(const double& Start, const double& End, float F);