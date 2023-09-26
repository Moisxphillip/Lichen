#ifndef LICHEN_TOOLS
#define LICHEN_TOOLS

// #include "../lib/IncludeAll.hpp"

#include <string>


struct ___ImageRect
{
    int x, y, w, h;
};

void Error(std::string Info);
int Fps(int RateInMs);
double WrapMax(double Val, double Max);
double WrapMinMax(double Val, double Min, double Max);
double Clamp(double Value);//Between 0 and 1
float SmootherStep(float LowerBound, float HigherBound, float x);
float SmoothStep (float LowerBound, float HigherBound, float x);

template <typename T>
T Lerp(const T& Start, const T& End, float Percent);


#endif//LICHEN_TOOLS