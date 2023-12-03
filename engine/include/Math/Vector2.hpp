#ifndef LICHEN_VECTOR2
#define LICHEN_VECTOR2

//C++ includes
#include <list>
#include <ostream>

class Vector2
{
    public:
        //Constructors
        Vector2(float, float);
        Vector2();
        //Variables
        union
        {
            float x, a, w;
        };
        union
        {
            float y, b, h;
        };

        static const Vector2 ZERO;        

        //Vector special operations
        float MagnitudeSquared();
        float Magnitude();
        float Angle();
        Vector2 Normalized();
        Vector2 Normalize();
        float Dot(const Vector2& Other);
        float DistanceSquared(const Vector2& Other);
        float Distance(const Vector2& Other);
        Vector2 DistVector2(const Vector2& Other);
        float DistAngle(const Vector2& Other);
        Vector2 Rotate(const float& Angle);
        Vector2 Rotated(const float& Angle);
        Vector2 MoveTo(const Vector2& Goal, const float& Speed);

        //Useful functions for external use
        static float Dot(const Vector2& A, const Vector2& B);
        static float DistanceSquared(const Vector2& A, const Vector2& B);
        static float Distance(const Vector2& A, const Vector2& B);
        static Vector2 DistVector2(const Vector2& A, const Vector2& B);
        static Vector2 Bezier(const Vector2& V0, const Vector2& V1, const Vector2& V2, float& T);
        static float DistAngle(const Vector2& A, const Vector2& B);
        static float DegToRad(const float& Degrees);
        static float RadToDeg(const float& Radians);
        
        //Operation overloads
        friend Vector2 operator+(const Vector2& A, const Vector2& B);
        friend Vector2 operator-(const Vector2& A, const Vector2& B);
        friend Vector2 operator*(const Vector2& A, const float& Scalar);
        friend Vector2 operator*(const float& Scalar, const Vector2& B);
        friend Vector2 operator*(const Vector2& A, const Vector2& B);
        friend Vector2 operator/(const Vector2& A, const float& Scalar);
        friend Vector2 operator/(const Vector2& A, const Vector2& B);
        friend bool operator==(const Vector2& A, const Vector2&);
        friend bool operator!=(const Vector2& A, const Vector2&);
        friend std::ostream& operator<<(std::ostream& Out, const Vector2& Vec);
        //=
        Vector2& operator=(const Vector2& Other);
        Vector2& operator=(const std::list<float>& List);
        Vector2& operator=(const std::list<int>& List);
        //+=, -=, *=
        Vector2& operator+=(const Vector2& Other);
        Vector2& operator-=(const Vector2& Other);
        Vector2& operator*=(const float& Scalar);
        Vector2& operator*=(const Vector2& Other);
        Vector2& operator/=(const float& Scalar);
        Vector2& operator/=(const Vector2& Other);

};  

#endif//LICHEN_VECTOR2