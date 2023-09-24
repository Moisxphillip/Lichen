#ifndef LICHEN_RECT
#define LICHEN_RECT

//Engine includes
#include "Math/Vector2.hpp"

class Vector2;
class Circle;

class Rectangle
{
    public:
        float x, y, w, h;
        //Constructors
        Rectangle(float X, float Y, float W, float H);
        Rectangle();
        //Functions
        Vector2 Position();
        Vector2 Dimensions();
        Vector2 Center();
        void SetPosition(Vector2 Position);
        void Redimension(const Vector2& Dimensions);
        void SetCenter(Vector2 CenterPoint);
        float DistCenters(Rectangle& Other);
        float DistCenters(Circle& Other);
        bool Contains(const Vector2& Position);
        Rectangle GetIntersection(Rectangle& Other);
        //+, -, <<
        friend Rectangle operator+(const Rectangle& A, const Vector2& B);
        friend Rectangle operator-(const Rectangle& A, const Vector2& B);
        friend Rectangle operator*(const Rectangle& A, const Vector2& B);
        friend Rectangle operator*(const Vector2& A, const Rectangle& B);
        friend Rectangle operator/(const Rectangle& A, const Vector2& B);
        friend bool operator==(const Rectangle& A, const Rectangle& B);
        friend bool operator!=(const Rectangle& A, const Rectangle& B);
        friend std::ostream& operator<<(std::ostream& A, const Rectangle& B);
        Rectangle(const Rectangle&); 
        //+=, -=,
        Rectangle& operator+=(const Vector2& Vec);
        Rectangle& operator-=(const Vector2& Vec);
        Rectangle& operator*=(const Vector2& Vec);
        Rectangle& operator/=(const Vector2& Vec);

};
#endif//LICHEN_RECT