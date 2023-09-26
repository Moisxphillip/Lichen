#include "Math/Circle.hpp"

Circle::Circle(float X, float Y, float R)
{
    x=X;
    y=Y;
    r=R;
}

Circle::Circle(Vector2 Pos, float R)
: Circle(Pos.x, Pos.y, R)
{
}

Circle::Circle()
: Circle(0.0f,0.0f,0.0f)
{
}

Vector2 Circle::Center()
{
    return Vector2(x,y);
}

Vector2 Circle::Corner()
{
    return Vector2(x-r,y-r);
}

void Circle::SetCorner(Vector2 Pos) //as if it is a square
{
    x = Pos.x-r;
    y = Pos.y-r;
}

void Circle::SetCenter(Vector2 Pos) //as if it is a square
{
    x = Pos.x;
    y = Pos.y;
}

float Circle::Area()
{
    return 3.14159265359f * r * r;
}

float Circle::Circumference()
{
    return 2.0f * 3.14159265359f * r;
}

bool Circle::Contains(Vector2 Point)
{
    float dx = Point.x - x;
    float dy = Point.y - y;
    return dx * dx + dy * dy <= r * r;
}

float Circle::DistCenters(Circle& Other)
{
    return (this->Center() - Other.Center()).Magnitude();
}

float Circle::DistCenters(Rectangle& Other)
{
    return (this->Center() - Other.Center()).Magnitude();
}

Circle operator+(const Circle& Other, const Vector2& Vector)
{
    return Circle(Other.x + Vector.x, Other.y + Vector.y, Other.r);
}

Circle operator-(const Circle& Other, const Vector2& Vector)
{
    return Circle(Other.x - Vector.x, Other.y - Vector.y, Other.r);
}

Circle operator*(const Circle& Other, const Vector2& Vector)
{
    return Circle(Other.x * Vector.x, Other.y * Vector.y, Other.r);
}

Circle operator*(const Vector2& Vector, const Circle& Other)
{
    return Circle(Other.x * Vector.x, Other.y * Vector.y, Other.r);
}

bool operator==(const Circle& R1, const Circle& R2)
{
    return (R1.x == R2.x && R1.y == R2.y && R1.r == R2.r);
}

bool operator!=(const Circle& R1, const Circle& R2)
{
    return !(R1==R2);
}

std::ostream& operator<<(std::ostream& Out, const Circle& Other)
{
    Out << "(x=" << Other.x << ",y=" << Other.y 
    << ", r=" << Other.r << ")";

    return Out;
}

Circle& Circle::operator+=(const Vector2& Vector)
{
    this->x+=Vector.x;
    this->y+=Vector.y;
    return *this;
}

Circle& Circle::operator-=(const Vector2& Vector)
{
    this->x-=Vector.x;
    this->y-=Vector.y;
    return *this;
}

Circle& Circle::operator*=(const Vector2& Vector)
{
    this->x*=Vector.x;
    this->y*=Vector.y;
    return *this;
}

Circle& Circle::operator/=(const Vector2& Vector)
{
    this->x/=Vector.x;
    this->y/=Vector.y;
    return *this;
}
