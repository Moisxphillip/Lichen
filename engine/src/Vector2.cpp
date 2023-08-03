#include <cmath>

#include "../lib/Vector2.hpp"

#define PI_DEG 0.0174532925199432957692f
#define DEG_PI 57.295779513082320876798f

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2()
{
    Vector2(0.0, 0.0);
}
//_____________________________________

float Vector2::Magnitude()
{
    return sqrt((this->x * this->x) + (this->y * this->y));
}

float Vector2::Angle()
{
    return atan2(this->y, this->x);
}

Vector2 Vector2::Normalized()
{
    float Mag = this->Magnitude();
    if(Mag == 0)
    {
        // Error("Vector2::Normalized: Division by zero must not occur");
        return Vector2(0,0);
    }
    return Vector2(this->x/Mag, this->y/Mag);
}

float Vector2::Dot(const Vector2& Vector)
{
    return (this->x* Vector.x + this->y*Vector.y);
}

float Vector2::Distance(const Vector2& Vector)
{
    return ((*this - Vector).Magnitude());
}

Vector2 Vector2::DistVector2(const Vector2& Vector)
{
    return (Vector - *this);
}

float Vector2::DistAngle(const Vector2& Vector)
{
    return ((Vector - *this).Angle());
}

Vector2 Vector2::Rotate(const float& Rad)
{
    float Sin = sin(Rad), Cos = cos(Rad);
    float x = this->x*Cos - this->y*Sin;
    float y = this->y*Cos + this->x*Sin;
    this->x = x;
    this->y = y;
    
    return *this;
}

//________________________________________
float Vector2::Dot(const Vector2& V1, const Vector2& V2)
{
    return (V1.x* V2.x + V1.y*V2.y);
}

float Vector2::Distance(const Vector2& V1, const Vector2& V2)
{
    return ((V1 - V2).Magnitude());
}

Vector2 Vector2::DistVector2(const Vector2& V1, const Vector2& V2)
{
    return (V2-V1);
}

float Vector2::DistAngle(const Vector2& V1, const Vector2& V2)
{
    return ((V2-V1).Angle());
}

float Vector2::DegToRad(const float& Deg)
{
    return (Deg*PI_DEG);
}

float Vector2::RadToDeg(const float& Rad)
{
    return (Rad*DEG_PI);
}

//_________________________________________________

Vector2 operator+(const Vector2& V1, const Vector2& V2)
{
    return Vector2(V1.x + V2.x, V1.y + V2.y);
}

Vector2 operator-(const Vector2& V1, const Vector2& V2)
{
    return Vector2(V1.x - V2.x, V1.y - V2.y);
}

Vector2 operator*(const Vector2& V1, const float& Scalar)
{
    return Vector2(V1.x * Scalar, V1.y * Scalar);
}

Vector2 operator*(const Vector2& V1, const Vector2& V2)
{
    return Vector2(V1.x * V2.x, V1.y * V2.y);
}

bool operator==(const Vector2& V1, const Vector2& V2)
{
    return (((abs(V1.x-V2.x) < 1e-9) && (abs(V1.y-V2.y) < 1e-9)) ? true : false);
}

bool operator!=(const Vector2& V1, const Vector2& V2)
{
    return !(V1 == V2);
}

std::ostream& operator<<(std::ostream& Out, const Vector2& Vector)
{
    Out << "(" << Vector.x << " , " << Vector.y << ")";
    return Out;
}

//___________________________________________

Vector2& Vector2::operator=(const std::list<float>& List)
{
    this->x = List.front();
    this->y = List.back();
    return *this;
}

Vector2& Vector2::operator=(const std::list<int>& List)
{
    this->x = float(List.front());
    this->y = float(List.back());
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& Vector)
{
    *this = *this + Vector;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& Vector)
{
    *this = *this - Vector;
    return *this;
}

Vector2& Vector2::operator*=(const float& Scalar)
{
    *this = *this * Scalar;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& Vector)
{
    *this = *this * Vector;
    return *this;
}