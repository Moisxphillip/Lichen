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

template <typename T>
T WrapMax(T Value, T Max);

template <typename T>
T WrapMinMax(T Value, T Min, T Max);

template <typename T>
T Clamp(T Value);

template <typename T>
T SmootherStep(T Value, T LowerBound, T HigherBound);

template <typename T>
T SmoothStep(T Value, T LowerBound, T HigherBound);

template <typename T>
T Attenuation(T Value, T GrowthEnd=0.2, T DecreasePoint=0.8);

template <typename T>
T Lerp(const T& Start, const T& End, float Percent);


#endif//LICHEN_TOOLS