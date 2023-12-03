#include "Tools/Color.hpp"
#include "Tools/Tools.hpp"
#include <iostream>
#include <iomanip>
// #define _USE_MATH_DEFINES


Color::Color()
{
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
}

Color::Color(std::string Hex)
{
    if(Hex.length() == 7)
    {
        uint32_t R, G, B;
        sscanf(Hex.substr(1,6).c_str(), "%02x%02x%02x", &R, &G, &B);
        this->r = R/255.0f;
        this->g = G/255.0f;
        this->b = B/255.0f;
        this->a = 1.0f; 
    }
    else if(Hex.length() == 9)
    {
        uint32_t R, G, B, A;
        sscanf(Hex.substr(1,8).c_str(), "%02x%02x%02x%02x", &R, &G, &B, &A);
        this->r = R/255.0f;
        this->g = G/255.0f;
        this->b = B/255.0f;
        this->a = A/255.0f; 
    }
}

Color::Color(float R, float G, float B, float A)
: r(R), g(G), b(B), a(A)
{
}

Color::Color(float R, float G, float B)
:Color(R,G,B,1.0f)
{
}

Color operator-(const Color& X, const Color& Y)
{
    Color C;
    C.r = Clamp(X.r - Y.r);
    C.g = Clamp(X.g - Y.g);
    C.b = Clamp(X.b - Y.b);
    C.a = Clamp(X.a - Y.a);
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
    C.r = Clamp(X.r + Y.r);
    C.g = Clamp(X.g + Y.g);
    C.b = Clamp(X.b + Y.b);
    C.a = Clamp(X.a + Y.a);
    return C;
}

Color& Color::operator+=(const Color& X)
{
    *this = *this + X;
    return *this;
}

bool operator==(const Color& C1, const Color& C2)
{
    return (C1.r == C2.r && C1.g == C2.g && C1.b == C2.b && C1.a == C2.a);
}

bool operator!=(const Color& C1, const Color& C2)
{
    return !(C1 == C2);
}

std::ostream& operator<<(std::ostream& Out, const Color& Colour)
{
    int r = (int)(Colour.r*255), g = (int)(Colour.g*255), b = (int)(Colour.b*255), a = (int)(Colour.a*255);
    Out << "#" << std::setw(2) << std::setfill('0') << std::hex << r << g << b << a; //Fix zero case later
    return Out;
}

SDL_Color Color::ColorSDL()
{
    SDL_Color Convert{(uint8_t)(r*255),(uint8_t)(g*255),(uint8_t)(b*255),(uint8_t)(a*255)};
    return Convert;
}

void Color::SetHSV(float H, float S, float V)
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
    
    *this = Color((r+m), (g+m), (b+m));
}

uint32_t Color::ColorUint32()
{
    SDL_Color ThisOne = ColorSDL();
	return (uint32_t)((uint8_t)((ThisOne.a*255) << 24) + (uint8_t)((ThisOne.r*255) << 16) + (uint8_t)(((ThisOne.g*255) << 8)) + (uint8_t)(((ThisOne.b*255) << 0)));
}

Color Color::Interpolation(Color& A, Color& B, float F)
{
    return Color(Lerp(A.r, B.r, F), Lerp(A.g, B.g, F), Lerp(A.b, B.b, F), Lerp(A.a, B.a, F));
}