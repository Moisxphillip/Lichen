#ifndef LICHEN_RECT
#define LICHEN_RECT

//Engine includes
#include "Vector2.hpp"

class Vector2;

class Rect
{
    public:
        float x, y, w, h;
        //Constructors
        Rect(float, float, float, float);
        Rect();
        //Functions
        Vector2 Position();
        Vector2 Dimensions();
        void Redimension(const Vector2&);
        Vector2 Center();
        void SetCenter(Vector2);
        float DistCenters(Rect&);
        bool Contains(const Vector2&);
        //+, -, <<
        friend Rect operator+(const Rect&, const Vector2&);
        friend Rect operator-(const Rect&, const Vector2&);
        friend Rect operator*(const Rect&, const Vector2&);
        friend bool operator==(const Rect&, const Rect&);
        friend bool operator!=(const Rect&, const Rect&);
        friend std::ostream& operator<<(std::ostream&, const Rect&);
        Rect(const Rect&); 
        //+=, -=,
        Rect& operator+=(const Vector2&);
        Rect& operator-=(const Vector2&);

};

    //=
    // Rect& operator=(const Rect&);
    // Rect(const Rect&);// Custom copy constructor
    // Rect& operator=(const Rect&);// Custom copy assignment operator
    // Rect(Rect&&);// Custom move constructor
    // Rect& operator=(Rect&&);// Custom move assignment operator
#endif//LICHEN_RECT