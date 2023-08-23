#include "../lib/Rect.hpp"

Rect::Rect(float x, float y, float w, float h)
: x(x),y(y),w(w),h(h)
{
}

Rect::Rect()
: Rect(0,0,0,0)
{
}

Vector2 Rect::Position()
{
    return Vector2(x,y);
}

Vector2 Rect::Dimensions()
{
    return Vector2(w,h);
}

void Rect::Redimension(const Vector2& Vector)
{
    w = Vector.w;
    h = Vector.h;
}

Vector2 Rect::Center()
{
    return Vector2(x+(w/2), y+(h/2));
}

void Rect::SetCenter(Vector2 Coord)
{
    x = Coord.x - w/2;
    y = Coord.y - h/2;
}

float Rect::DistCenters(Rect& Other)
{
    return (this->Center() - Other.Center()).Magnitude();
}

bool Rect::Contains(const Vector2& Vector)
{
    return ((Vector.x >= x) 
        && (Vector.y >= y)
        && (Vector.x <= (x+w))
        && (Vector.y <= (y+h)));
}       

//+, -, <<
Rect operator+(const Rect& Other, const Vector2& Vector)
{
    return Rect(Other.x + Vector.x, Other.y + Vector.y, Other.w, Other.h);
}

Rect operator-(const Rect& Other, const Vector2& Vector)
{
    return Rect(Other.x - Vector.x, Other.y - Vector.y, Other.w, Other.h);
}

Rect operator*(const Rect& Other, const Vector2& Vector)
{
    return Rect(Other.x * Vector.x, Other.y * Vector.y, Other.w, Other.h);
}

bool operator==(const Rect& R1, const Rect& R2)
{
    return (R1.x == R2.x && R1.y == R2.y && R1.w == R2.w && R1.h == R2.h);
}

bool operator!=(const Rect& R1, const Rect& R2)
{
    return !(R1==R2);
}


std::ostream& operator<<(std::ostream& Out, const Rect& Other)
{
    Out << "(x=" << Other.x << ",y=" << Other.y 
    << ", w=" << Other.w << ",h=" << Other.h << ")";

    return Out;
}

//+=, -=,
Rect& Rect::operator+=(const Vector2& Vector)
{
    this->x+=Vector.x;
    this->y+=Vector.y;
    return *this;
}

Rect& Rect::operator-=(const Vector2& Vector)
{
    this->x-=Vector.x;
    this->y-=Vector.y;
    return *this;
}

Rect::Rect(const Rect& Other) 
{
    if (this != &Other) 
    {
        x = Other.x;
        y = Other.y;
        w = Other.w;
        h = Other.h;
    }
}

// // Custom copy assignment operator
// Rect& Rect::operator=(const Rect& Other) 
// {
//     if (this != &Other) 
//     {
//         Position = Other.Position;
//         Dimension = Other.Dimension;
//     }
//     return *this;
// }

// // Custom move constructor
// Rect::Rect(Rect&& Other) 
// {
//     Position = std::move(Other.Position);
//     Dimension = std::move(Other.Dimension);
// }

// // Custom move assignment operator
// Rect& Rect::operator=(Rect&& Other) 
// {
//     if (this != &Other) 
//     {
//         Position = std::move(Other.Position);
//         Dimension = std::move(Other.Dimension);
//     }
//     return *this;
// }


// //=
// Rect& Rect::operator=(const Rect& Other)
// {
//     x = Other.x;
//     y = Other.y;
//     w = Other.w;
//     h = Other.h;
//     return *this;
// }