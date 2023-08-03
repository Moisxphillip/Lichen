#include "../lib/Color.hpp"
#include <iostream>
// #define _USE_MATH_DEFINES


Color::Color()
{
    R = 0;
    G = 0;
    B = 0;
    A = 0;
}

Color::Color(std::string Hex)
{
    if(Hex.length() == 7)
    {
        uint32_t R, G, B;
        sscanf(Hex.substr(1,6).c_str(), "%02x%02x%02x", &R, &G, &B);
        this->R = R;
        this->G = G;
        this->B = B;
        this->A = 0; 
    }
    else if(Hex.length() == 9)
    {
        uint32_t R, G, B, A;
        sscanf(Hex.substr(1,8).c_str(), "%02x%02x%02x%02x", &R, &G, &B, &A);
        this->R = R;
        this->G = G;
        this->B = B;
        this->A = A; 
    }
}

Color::Color(uint8_t R, uint8_t G, uint8_t B)
{
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = 0;
}

Color::Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
: Color(R, G, B)
{
    this->A = A;
}

Color operator-(const Color& X, const Color& Y)
{
    Color C;
    C.R = X.R - Y.R;
    C.G = X.G - Y.G;
    C.B = X.B - Y.B;
    C.A = X.A - Y.A;
    return C;
}

Color& Color::operator-=(const Color& X)
{
    *this = *this - X;
    return *this;
}

Color operator+(const Color& X, const Color& Y)
{
    Color C;
    C.R = X.R + Y.R;
    C.G = X.G + Y.G;
    C.B = X.B + Y.B;
    C.A = X.A + Y.A;
    return C;
}

Color& Color::operator+=(const Color& X)
{
    *this = *this + X;
    return *this;
}

std::ostream& operator<<(std::ostream& Out, const Color& Colour)
{
    Out << "#" << std::hex << Colour.R << Colour.G << Colour.B << Colour.A;
    return Out;
}

SDL_Color Color::ColorSDL()
{
    SDL_Color Convert{R,G,B,A};
    return Convert;
}

void Color::SetHSV(float H, float S,float V)
{
    ((H > 360 || H < 0) ? H = fmod(H, 360) : H);
    ((S > 100 || S < 0) ? H = fmod(H, 100) : S);
    ((V > 100 || V < 0) ? H = fmod(H, 100) : V);

    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;

    if(H >= 0 && H < 60)
    {
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120)
    {
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180)
    {
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240)
    {
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300)
    {
        r = X,g = 0,b = C;
    }
    else
    {
        r = C,g = 0,b = X;
    }
    
    *this = Color((r+m)*255, (g+m)*255, (b+m)*255);
}

uint32_t Color::ColorUint32()
{
	return (uint32_t)((this->R << 16) + (this->G << 8) + (this->B << 0));
}