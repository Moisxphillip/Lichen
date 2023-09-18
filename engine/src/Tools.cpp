#include "../lib/Tools.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>
// #include "SDL2/SDL.h"

void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    // std::cout << SDL_GetError() << ".\n";
    //TODO call exit(-1) on error
}

int Fps(int Rate) //Takes intended frames per second and returns approximated time of each frame in ms
{
    return 1000/Rate;
}

double WrapMax(double Val, double Max)
{
    return fmod(Max + fmod(Val, Max), Max);
}

//Val -> [Min,Max)
double WrapMinMax(double Val, double Min, double Max)
{
    return Min + WrapMax(Val - Min, Max - Min);
}

double Clamp(double x) 
{
    return (x<0?0:(x>1?1:x));
}

double SmootherStep (double LowerBound, double HigherBound, double x) 
{
    x = Clamp((x - LowerBound) / (HigherBound - LowerBound));
    return x * x * x * (x * (x * 6 - 15) + 10);
}

double SmoothStep (double LowerBound, double HigherBound, double x) 
{
    x = Clamp((x - LowerBound) / (HigherBound - LowerBound));
    return x * x * (3 - 2 * x);
}

template <typename T>
T Lerp(const T& Start, const T& End, float F) 
{
    F = std::clamp(F, 0.0f, 1.0f);
    return Start + F * (End - Start);
}
template float Lerp(const float& Start, const float& End, float F);
template double Lerp(const double& Start, const double& End, float F);