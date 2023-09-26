#include "Tools/xrand.hpp"

//Unsigned int Generation
XrandU64::XrandU64()
{
    seed(0);
    range(0, ULLONG_MAX);
}
XrandU64::XrandU64(uint64_t Seed)//Sets seed at start
{
    seed(Seed);
    range(0, ULLONG_MAX);
}

void XrandU64::seed(uint64_t seed)//Takes an unsigned integer and sets as the seed based in the 1st state from the shiftmix
{
    currseed = seed;
    currstate = ___shiftmix64(seed);
}

void XrandU64::range(uint64_t floor, uint64_t ceil)//Gets the minimum and maximum values for generation range
{
    if(floor > ceil)
    {
        std::swap(floor, ceil);
    }
    minimum = floor;
    dist = ceil - floor;
    (dist != ULLONG_MAX ? dist++ : dist);
    ceiling = (dist < ULLONG_MAX-1 ? ULLONG_MAX - (ULLONG_MAX % dist) + 1 : ULLONG_MAX) ; //+1 because of the zero usage limitation 
}

uint64_t XrandU64::gen()//Returns an unsigned integer between the range specified on init or .range()
{
    bool trim = true;
    uint64_t res;
    while(trim)
    {
        res = ___xorshift64star(currstate);
        if (res <= ceiling)
        {
            trim = false;
        }
        currstate = res;
    }
    if(dist != ULLONG_MAX)
    {
        return (res % dist) + minimum;
    }
    return res;        
}

uint64_t XrandU64::min()//Returns the minimum value from the set range
{
    return minimum;
}

uint64_t XrandU64::max()//Returns the maximum value from the set range
{
    return dist - 1 + minimum;
}

uint64_t XrandU64::___shiftmix64(uint64_t state)//A generator based in the shiftmix method
{
    uint64_t z = (state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
}

uint64_t XrandU64::___xorshift64star(uint64_t state)//xorshift64s, variant A_1(12,25,27) with multiplier M_32 from line 3 of table 5
{
    uint64_t x;
    if(state != 0)/* initial seed must be nonzero, don't use a static variable for the state if multithreaded */
    {
        x = state;
    }
    else
    {
        x = ___shiftmix64(currseed);
    } 
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    return x * 0x2545F4914F6CDD1DULL;
}

//Floating Point Generation
XrandF32::XrandF32()
{
}

XrandF32::XrandF32(uint64_t Seed)//Sets seed at start
{
    _xor64.seed(Seed);
}

float XrandF32::gen()//Returns a floating point number between 0.0 and 1.0
{
    return _xor64.gen()/18446744073709551616.0; 
}

void XrandF32::seed(uint64_t Seed) //Takes an unsigned integer and sets as the seed based in the 1st state from the shiftmix
{
    _xor64.seed(Seed);
}