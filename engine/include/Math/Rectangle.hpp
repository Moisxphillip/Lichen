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
        Rectangle(float, float, float, float);
        Rectangle();
        //Functions
        Vector2 Position();
        Vector2 Dimensions();
        Vector2 Center();
        void SetPosition(Vector2);
        void Redimension(const Vector2&);
        void SetCenter(Vector2);
        float DistCenters(Rectangle&);
        float DistCenters(Circle&);
        bool Contains(const Vector2&);
        Rectangle GetIntersection(Rectangle& Other);
        //+, -, <<
        friend Rectangle operator+(const Rectangle&, const Vector2&);
        friend Rectangle operator-(const Rectangle&, const Vector2&);
        friend Rectangle operator*(const Rectangle&, const Vector2&);
        friend Rectangle operator*(const Vector2&, const Rectangle&);
        friend Rectangle operator/(const Rectangle&, const Vector2&);
        friend bool operator==(const Rectangle&, const Rectangle&);
        friend bool operator!=(const Rectangle&, const Rectangle&);
        friend std::ostream& operator<<(std::ostream&, const Rectangle&);
        Rectangle(const Rectangle&); 
        //+=, -=,
        Rectangle& operator+=(const Vector2&);
        Rectangle& operator-=(const Vector2&);
        Rectangle& operator*=(const Vector2&);
        Rectangle& operator/=(const Vector2&);

};
#endif//LICHEN_RECT