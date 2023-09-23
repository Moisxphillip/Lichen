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
        

        //Vector special operations
        float MagnitudeSquared();
        float Magnitude();
        float Angle();
        Vector2 Normalized();
        Vector2 Normalize();
        float Dot(const Vector2&);
        float DistanceSquared(const Vector2&);
        float Distance(const Vector2&);
        Vector2 DistVector2(const Vector2&);
        float DistAngle(const Vector2&);
        Vector2 Rotate(const float& Angle);
        Vector2 Rotated(const float& Angle);
        Vector2 MoveTo(const Vector2& Goal, const float& Speed);

        //Useful functions for external use
        static float Dot(const Vector2&, const Vector2&);
        static float DistanceSquared(const Vector2&, const Vector2&);
        static float Distance(const Vector2&, const Vector2&);
        static Vector2 DistVector2(const Vector2&, const Vector2&);
        static Vector2 Bezier(const Vector2& V0, const Vector2& V1, const Vector2& V2, float& T);
        static float DistAngle(const Vector2&, const Vector2&);
        static float DegToRad(const float&);
        static float RadToDeg(const float&);
        
        //Operation overloads
        friend Vector2 operator+(const Vector2&, const Vector2&);
        friend Vector2 operator-(const Vector2&, const Vector2&);
        friend Vector2 operator*(const Vector2&, const float&);
        friend Vector2 operator*(const float&, const Vector2&);
        friend Vector2 operator*(const Vector2&, const Vector2&);
        friend Vector2 operator/(const Vector2&, const float&);
        friend Vector2 operator/(const Vector2&, const Vector2&);
        friend bool operator==(const Vector2&, const Vector2&);
        friend bool operator!=(const Vector2&, const Vector2&);
        friend std::ostream& operator<<(std::ostream&, const Vector2&);
        //=
        Vector2& operator=(const Vector2&);
        Vector2& operator=(const std::list<float>&);
        Vector2& operator=(const std::list<int>&);
        //+=, -=, *=
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2& operator*=(const float&);
        Vector2& operator*=(const Vector2&);

};  

#endif//LICHEN_VECTOR2