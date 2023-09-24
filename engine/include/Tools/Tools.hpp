#ifndef LICHEN_TOOLS
#define LICHEN_TOOLS

// #include "../lib/IncludeAll.hpp"

#include <string>


struct ___ImageRect
{
    int x, y, w, h;
};

void Error(std::string);
int Fps(int);
double WrapMax(double, double);
double WrapMinMax(double, double, double);
double Clamp(double);
float SmootherStep(float LowerBound, float HigherBound, float x);
float SmoothStep (float LowerBound, float HigherBound, float x);

template <typename T>
T Lerp(const T& start, const T& end, float t);


#endif//LICHEN_TOOLS