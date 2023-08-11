#ifndef LICHEN_RECT
#define LICHEN_RECT

//Engine includes
#include "Vector2.hpp"

class Vector2;

class Rect
{
    public:
        //Variables
        float x, y, w, h;
        //Constructors
        Rect(float, float, float, float);
        Rect();
        //Functions
        void AddVector2(const Vector2&);
        void Redimension(const Vector2&);
        Vector2 Center();
        void SetCenter(Vector2);
        float DistCenters(Rect&);
        bool Contains(const Vector2&);
        //+, -, <<
        friend Rect operator+(const Rect&, const Vector2&);
        friend Rect operator-(const Rect&, const Vector2&);
        friend Rect operator*(const Rect&, const Vector2&);
        friend std::ostream& operator<<(std::ostream&, const Rect&);
        //+=, -=,
        Rect& operator+=(const Vector2&);
        Rect& operator-=(const Vector2&);

};



#endif//LICHEN_RECT