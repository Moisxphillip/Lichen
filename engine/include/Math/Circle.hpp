#ifndef LICHEN_CIRCLE
#define LICHEN_CIRCLE

#include "Math/Vector2.hpp"
#include "Math/Rectangle.hpp"

class Circle
{
    public:
        float x, y, r;

        Circle(float, float, float);
        Circle(Vector2, float);
        Circle();
        Vector2 Center();
        Vector2 Corner();
        void SetCorner(Vector2 Pos);
        void SetCenter(Vector2 Pos);
        float Area();
        float Circumference();
        bool Contains(Vector2);
        float DistCenters(Rectangle&);
        float DistCenters(Circle&);

        friend Circle operator+(const Circle&, const Vector2&);
        friend Circle operator-(const Circle&, const Vector2&);
        friend Circle operator*(const Circle&, const Vector2&);
        friend Circle operator*(const Vector2&, const Circle&);
        friend Circle operator/(const Circle&, const Vector2&);
        friend bool operator==(const Circle&, const Circle&);
        friend bool operator!=(const Circle&, const Circle&);
        friend std::ostream& operator<<(std::ostream&, const Circle&);
        Circle& operator+=(const Vector2&);
        Circle& operator-=(const Vector2&);
        Circle& operator*=(const Vector2&);
        Circle& operator/=(const Vector2&);
};

#endif//LICHEN_CIRCLE
