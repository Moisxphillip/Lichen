#ifndef LICHEN_SETTINGS
#define LICHEN_SETTINGS

#include "SDL2/SDL_image.h"
//Definitions for quick changes across all project files

#define LICHEN_SCRTITLE "Moises Felipe Jaco Andrade de Lima - 190018364 | Fog"
#define LICHEN_SCRWIDTH 1024
#define LICHEN_SCRHEIGHT 600
#define LICHEN_SOUNDCHANNELS 32

#define ROTFRAC (M_PI/4)
#define LICHEN_BULLETSPD 300.f
#define LICHEN_ALIENSPD 170.f
#define LICHEN_BULLETDIST 900.f
#define LICHEN_BULLETDMG 15
#define LICHEN_NUMMINIONS 5
#define LICHEN_PENGACCEL 100
#define LICHEN_PENGSPDMAX 250.f
#define LICHEN_DEATHFRAMETIME 0.15


//TODO implement a class that controls the screen info, reading configs
//from a file or creating a file with the default settings.


// enum Uses //Bitwise-based flags Unnecessary bit-brushing
// {
//     None = 0,
//     All = 0xFFFF,
//     Collision = 1 << 0,
//     Render = 1 << 1,
//     Start =  1 << 2,
//     Update = 1 << 3
// };

// inline Uses operator|(Uses a, Uses b)
// {
//     return static_cast<Uses>(static_cast<int>(a) | static_cast<int>(b));
// }


typedef enum
{
    N = SDL_FLIP_NONE,
    H = SDL_FLIP_HORIZONTAL,
    V = SDL_FLIP_VERTICAL,
    HV = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
} Flip;

inline Flip operator|(Flip a, Flip b)
{
    return static_cast<Flip>(static_cast<int>(a) | static_cast<int>(b));
}

#endif//LICHEN_SETTINGS