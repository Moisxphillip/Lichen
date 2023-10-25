#include <cmath>

#include "Math/Vector2.hpp"
#include "Tools/Tools.hpp"

#define PI_DEG 0.0174532925199432957692f
#define DEG_PI 57.295779513082320876798f

Vector2::Vector2(float x, float y)
: x(x), y(y)
{
}

Vector2::Vector2()
: Vector2(0.0, 0.0)
{
}
//_____________________________________

float Vector2::MagnitudeSquared()
{
    return (this->x * this->x) + (this->y * this->y);
}

float Vector2::Magnitude()
{
    return sqrt(MagnitudeSquared());
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
        Error("Vector2::Normalized: Division by zero must not occur");
        return Vector2(0,0);
    }
    return Vector2(this->x/Mag, this->y/Mag);
}

Vector2 Vector2::Normalize()
{
    float Mag = this->Magnitude();
    if(Mag == 0)
    {
        Error("Vector2::Normalized: Division by zero must not occur");
        return *this;
    }
    this->x/=Mag;
    this->y/=Mag;
    return *this;
}

float Vector2::Dot(const Vector2& Vector)
{
    return (this->x* Vector.x + this->y*Vector.y);
}

float Vector2::DistanceSquared(const Vector2& Vector)
{
    return ((*this - Vector).MagnitudeSquared());
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

Vector2 Vector2::Rotated(const float& Rad)
{
    float Sin = sin(Rad), Cos = cos(Rad);
    float x = this->x*Cos - this->y*Sin;
    float y = this->y*Cos + this->x*Sin;    
    return Vector2(x,y);
}

Vector2 Vector2::MoveTo(const Vector2& Goal, const float& Speed)
{
    Vector2 Movement = Goal - *this;
    float Mag = Movement.Magnitude();
    if(Mag <= Speed || Mag == 0)
    {
        *this = Goal;
        return Movement;
    }
    Movement = Movement/Mag * Speed;
    *this += Movement;
    return Movement;
}

//________________________________________
float Vector2::Dot(const Vector2& V1, const Vector2& V2)
{
    return (V1.x* V2.x + V1.y*V2.y);
}

float Vector2::DistanceSquared(const Vector2& V1, const Vector2& V2)
{
    return ((V1 - V2).MagnitudeSquared());
}

float Vector2::Distance(const Vector2& V1, const Vector2& V2)
{
    return ((V1 - V2).Magnitude());
}

Vector2 Vector2::DistVector2(const Vector2& V1, const Vector2& V2)
{
    return (V2-V1);
}

Vector2 Vector2::Bezier(const Vector2& V0, const Vector2& V1, const Vector2& V2, float& T)
{
    float InverseT = 1.0 - T;
    float T2 = T * T;
    return InverseT * InverseT * V0 + Vector2(2.0f, 2.0f) * InverseT * T * V1*V1 + T2 * V2;//remove one of the V1 later if needed

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

Vector2 operator*(const float& Scalar, const Vector2& V1)
{
    return V1 * Scalar;
}

Vector2 operator*(const Vector2& V1, const Vector2& V2)
{
    return Vector2(V1.x * V2.x, V1.y * V2.y);
}

Vector2 operator/(const Vector2& V1, const float& Scalar)
{
    return Vector2(V1.x / Scalar, V1.y / Scalar);
}

Vector2 operator/(const Vector2& V1, const Vector2& V2)
{
    return Vector2(V1.x / V2.x, V1.y / V2.y);
}

bool operator==(const Vector2& V1, const Vector2& V2)
{
    return (((abs(V1.x-V2.x) < 1e-4) && (abs(V1.y-V2.y) < 1e-4)));
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

Vector2& Vector2::operator=(const Vector2& Vec)
{
    this->x = Vec.x;
    this->y = Vec.y;
    return *this;
}
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
    this->x+=Vector.x;
    this->y+=Vector.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& Vector)
{
    this->x-=Vector.x;
    this->y-=Vector.y;
    return *this;
}

Vector2& Vector2::operator*=(const float& Scalar)
{
    this->x*=Scalar;
    this->y*=Scalar;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& Vector)
{
    this->x*=Vector.x;
    this->y*=Vector.y;
    return *this;
}

Vector2& Vector2::operator/=(const float& Scalar)
{
    this->x/=Scalar;
    this->y/=Scalar;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& Vector)
{
    this->x/=Vector.x;
    this->y/=Vector.y;
    return *this;
}