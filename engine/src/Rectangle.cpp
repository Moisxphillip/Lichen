#include "../lib/Rectangle.hpp"

Rectangle::Rectangle(float x, float y, float w, float h)
: x(x),y(y),w(w),h(h)
{
}

Rectangle::Rectangle()
: Rectangle(0,0,0,0)
{
}

Vector2 Rectangle::Position()
{
    return Vector2(x,y);
}

Vector2 Rectangle::Dimensions()
{
    return Vector2(w,h);
}

void Rectangle::Redimension(const Vector2& Vector)
{
    w = Vector.w;
    h = Vector.h;
}

Vector2 Rectangle::Center()
{
    return Vector2(x+(w/2), y+(h/2));
}

void Rectangle::SetCenter(Vector2 Coord)
{
    x = Coord.x - w/2;
    y = Coord.y - h/2;
}

void Rectangle::SetPosition(Vector2 Coord)
{
    x = Coord.x;
    y = Coord.y;
}

float Rectangle::DistCenters(Rectangle& Other)
{
    return (this->Center() - Other.Center()).Magnitude();
}

bool Rectangle::Contains(const Vector2& Vector)
{
    return ((Vector.x >= x) 
        && (Vector.y >= y)
        && (Vector.x <= (x+w))
        && (Vector.y <= (y+h)));
}       

//+, -, <<
Rectangle operator+(const Rectangle& Other, const Vector2& Vector)
{
    return Rectangle(Other.x + Vector.x, Other.y + Vector.y, Other.w, Other.h);
}

Rectangle operator-(const Rectangle& Other, const Vector2& Vector)
{
    return Rectangle(Other.x - Vector.x, Other.y - Vector.y, Other.w, Other.h);
}

Rectangle operator*(const Rectangle& Other, const Vector2& Vector)
{
    return Rectangle(Other.x * Vector.x, Other.y * Vector.y, Other.w, Other.h);
}

bool operator==(const Rectangle& R1, const Rectangle& R2)
{
    return (R1.x == R2.x && R1.y == R2.y && R1.w == R2.w && R1.h == R2.h);
}

bool operator!=(const Rectangle& R1, const Rectangle& R2)
{
    return !(R1==R2);
}


std::ostream& operator<<(std::ostream& Out, const Rectangle& Other)
{
    Out << "(x=" << Other.x << ",y=" << Other.y 
    << ", w=" << Other.w << ",h=" << Other.h << ")";

    return Out;
}

//+=, -=,
Rectangle& Rectangle::operator+=(const Vector2& Vector)
{
    this->x+=Vector.x;
    this->y+=Vector.y;
    return *this;
}

Rectangle& Rectangle::operator-=(const Vector2& Vector)
{
    this->x-=Vector.x;
    this->y-=Vector.y;
    return *this;
}

Rectangle::Rectangle(const Rectangle& Other) 
{
    if (this != &Other) 
    {
        x = Other.x;
        y = Other.y;
        w = Other.w;
        h = Other.h;
    }
}