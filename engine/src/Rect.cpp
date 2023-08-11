#include "../lib/Rect.hpp"

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::Rect()
{
    Rect(0, 0, 0, 0);
}

void Rect::AddVector2(const Vector2& Vector)
{
    this->x += Vector.x;
    this->y += Vector.y;
}

void Rect::Redimension(const Vector2& Vector)
{
    this->w = Vector.x;
    this->h = Vector.y;
}

Vector2 Rect::Center()
{
    return Vector2(x+(w/2), y+(h/2));
}

void Rect::SetCenter(Vector2 Coord)
{
    this->x = Coord.x - w/2;
    this->y = Coord.y - h/2;
}

float Rect::DistCenters(Rect& Rectangle)
{
    return (this->Center() - Rectangle.Center()).Magnitude();
}

bool Rect::Contains(const Vector2& Vector)
{
    return ((Vector.x >= this->x) 
        && (Vector.y >= this->y)
        && (Vector.x <= (this->x+this->w))
        && (Vector.y <= (this->y+this->h)));
}       

//+, -, <<
Rect operator+(const Rect& Rectangle, const Vector2& Vector)
{
    return Rect(Rectangle.x + Vector.x, Rectangle.y + Vector.y, Rectangle.w, Rectangle.h);
}

Rect operator-(const Rect& Rectangle, const Vector2& Vector)
{
    return Rect(Rectangle.x - Vector.x, Rectangle.y - Vector.y, Rectangle.w, Rectangle.h);
}

Rect operator*(const Rect& Rectangle, const Vector2& Vector)
{
    return Rect(Rectangle.x * Vector.x, Rectangle.y * Vector.y, Rectangle.w, Rectangle.h);
}

std::ostream& operator<<(std::ostream& Out, const Rect& Rectangle)
{
    Out << "Pos" << Rectangle.x << ',' << Rectangle.y << "), Size(" 
    << Rectangle.w << ',' << Rectangle.h << ")";

    return Out;
}

//+=, -=,
Rect& Rect::operator+=(const Vector2& Vector)
{
    *this = *this+Vector;
    return *this;
}

Rect& Rect::operator-=(const Vector2& Vector)
{
    *this = *this-Vector;
    return *this;
}