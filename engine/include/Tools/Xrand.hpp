#ifndef __XRAND__HEADER
#define __XRAND__HEADER
#include <stdint.h>
#include <climits>
#include <algorithm>


class XrandU64 //Generates unsigned integers between 0x1 and 0xFFFFFFFFFFFFFFFF
{
    public:
        XrandU64();
        XrandU64(uint64_t Seed);
        void seed(uint64_t Value);
        void range(uint64_t Min, uint64_t Max);
        uint64_t min();
        uint64_t max();
        uint64_t gen();
    private:
        uint64_t currseed;
        uint64_t currstate;
        uint64_t minimum;
        uint64_t dist;
        uint64_t ceiling;
        uint64_t ___shiftmix64(uint64_t Value);
        uint64_t ___xorshift64star(uint64_t Value);
};

class XrandF32 //Generates float numbers between 0 and 1
{
    public:
        XrandF32();
        XrandF32(uint64_t Seed);
        void seed(uint64_t Value);
        float gen();
        float min(){return 0.0;};//Minimum value generated
        float max(){return 1.0;};//Maximum value generated
    private:
        XrandU64 _xor64;
        
};

#endif//__XRAND__HEADER