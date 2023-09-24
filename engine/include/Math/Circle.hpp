#ifndef LICHEN_CIRCLE
#define LICHEN_CIRCLE

#include "Math/Vector2.hpp"
#include "Math/Rectangle.hpp"

class Circle
{
    public:
        float x, y, r;

        Circle(float X, float Y, float Radius);
        Circle(Vector2 Dimensions, float Radius);
        Circle();
        Vector2 Center();
        Vector2 Corner();
        void SetCorner(Vector2 Pos);
        void SetCenter(Vector2 Pos);
        float Area();
        float Circumference();
        bool Contains(Vector2 Pos);
        float DistCenters(Rectangle& Other);
        float DistCenters(Circle& Other);

        friend Circle operator+(const Circle& A, const Vector2& B);
        friend Circle operator-(const Circle& A, const Vector2& B);
        friend Circle operator*(const Circle& A, const Vector2& B);
        friend Circle operator*(const Vector2& A, const Circle& B);
        friend Circle operator/(const Circle& A, const Vector2& B);
        friend bool operator==(const Circle& A, const Circle& B);
        friend bool operator!=(const Circle& A, const Circle& B);
        friend std::ostream& operator<<(std::ostream& Out, const Circle& Form);
        Circle& operator+=(const Vector2& Vec);
        Circle& operator-=(const Vector2& Vec);
        Circle& operator*=(const Vector2& Vec);
        Circle& operator/=(const Vector2& Vec);
};

#endif//LICHEN_CIRCLE
