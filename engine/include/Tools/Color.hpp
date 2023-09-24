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
        float r, g, b, a;        
        Color();
        Color(std::string);
        // Color(uint8_t, uint8_t, uint8_t, uint8_t);
        // Color(uint8_t, uint8_t, uint8_t);
        Color(float, float, float);
        Color(float, float, float, float);

        void SetHSV(float, float, float);

        friend Color operator+(const Color&, const Color&);
        Color& operator+=(const Color&);
        friend Color operator-(const Color&, const Color&);
        Color& operator-=(const Color&);
        friend bool operator==(const Color&, const Color&);
        friend bool operator!=(const Color&, const Color&);
        friend std::ostream& operator<<(std::ostream&, const Color&);

        static Color Interpolation(Color& A, Color& B, float F);

        SDL_Color ColorSDL();
        uint32_t ColorUint32();

};

#endif// LICHEN_COLOR
