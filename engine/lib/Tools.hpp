#ifndef LICHEN_TOOLS
#define LICHEN_TOOLS

// #include "../lib/IncludeAll.hpp"

#include <string>

void Error(std::string);
int Fps(int);
double WrapMax(double, double);
double WrapMinMax(double, double, double);
double Clamp(double);
float SmootherStep(float LowerBound, float HigherBound, float x);
float SmoothStep (float LowerBound, float HigherBound, float x);



#endif//LICHEN_TOOLS