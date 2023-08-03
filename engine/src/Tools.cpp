#include "../lib/Tools.hpp"

#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"

void Error(std::string Info)
{
    std::cout << "Error! " << Info << ".\n";
    std::cout << SDL_GetError() << ".\n";
    //TODO call exit(-1) on error
}

int Fps(int Rate) //Takes intended frames per second and returns approximated time of each frame
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

double Clamp(double x) {
    return (x<0?0:(x>1?1:x));
}

double SmootherStep (double LowerBound, double HigherBound, double x) {
    x = Clamp((x - LowerBound) / (HigherBound - LowerBound));
    return x * x * x * (x * (x * 6 - 15) + 10);
}

double SmoothStep (double LowerBound, double HigherBound, double x) {
    x = Clamp((x - LowerBound) / (HigherBound - LowerBound));
    return x * x * (3 - 2 * x);
}
