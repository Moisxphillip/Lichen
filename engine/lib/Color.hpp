#ifndef LICHEN_COLOR
#define LICHEN_COLOR

#include <cmath>
#include <cstdint>
#include <string>

#include "SDL2/SDL_image.h"


class Color
{
    private:

    public:
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
        
        Color();
        Color(std::string);
        Color(uint8_t, uint8_t, uint8_t);
        Color(uint8_t, uint8_t, uint8_t, uint8_t);

        void SetHSV(float, float, float);

        friend Color operator+(const Color&, const Color&);
        Color& operator+=(const Color&);
        friend Color operator-(const Color&, const Color&);
        Color& operator-=(const Color&);
        friend std::ostream& operator<<(std::ostream&, const Color&);

        SDL_Color ColorSDL();
        uint32_t ColorUint32();

};

#endif// LICHEN_COLOR
