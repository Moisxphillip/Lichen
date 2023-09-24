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
        Color(std::string HexCode);

        Color(float R, float G, float B);
        Color(float R, float G, float B, float A);

        void SetHSV(float H, float S, float V);

        friend Color operator+(const Color&, const Color&);
        Color& operator+=(const Color&);
        friend Color operator-(const Color&, const Color&);
        Color& operator-=(const Color&);
        friend bool operator==(const Color&, const Color&);
        friend bool operator!=(const Color&, const Color&);
        friend std::ostream& operator<<(std::ostream& Out, const Color& Colour);

        static Color Interpolation(Color& A, Color& B, float Percent);

        SDL_Color ColorSDL();
        uint32_t ColorUint32();

};

#endif// LICHEN_COLOR
