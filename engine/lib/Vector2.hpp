#ifndef LICHEN_VECTOR2
#define LICHEN_VECTOR2

//C++ includes
#include <list>
#include <ostream>

class Vector2
{
    public:
        //Variables
        float x, y;
        //Constructors
        Vector2();
        Vector2(float, float);
        //Vector special operations
        float Magnitude();
        float Angle();
        Vector2 Normalized();
        float Dot(const Vector2&);
        float Distance(const Vector2&);
        Vector2 DistVector2(const Vector2&);
        float DistAngle(const Vector2&);
        Vector2 Rotate(const float&);
        //Useful functions for external use
        static float Dot(const Vector2&, const Vector2&);
        static float Distance(const Vector2&, const Vector2&);
        static Vector2 DistVector2(const Vector2&, const Vector2&);
        static float DistAngle(const Vector2&, const Vector2&);
        static float DegToRad(const float&);
        static float RadToDeg(const float&);
        //Operation overloads
        friend Vector2 operator+(const Vector2&, const Vector2&);
        friend Vector2 operator-(const Vector2&, const Vector2&);
        friend Vector2 operator*(const Vector2&, const float&);
        friend Vector2 operator*(const Vector2&, const Vector2&);
        friend bool operator==(const Vector2&, const Vector2&);
        friend bool operator!=(const Vector2&, const Vector2&);
        friend std::ostream& operator<<(std::ostream&, const Vector2&);
        //=
        Vector2& operator=(const std::list<float>&);
        Vector2& operator=(const std::list<int>&);
        //+=, -=, *=
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2& operator*=(const float&);
        Vector2& operator*=(const Vector2&);

};  

#endif//LICHEN_VECTOR2