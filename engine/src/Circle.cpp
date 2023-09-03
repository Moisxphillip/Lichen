#include "../lib/Circle.hpp"

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

Vector2 Circle::Position()
{
    return Vector2(x,y);
}

void Circle::SetCorner(Vector2 Pos) //as if it is a square
{
    x = Pos.x-r;
    y = Pos.y-r;
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