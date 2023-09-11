#ifndef LICHEN_CIRCLE
#define LICHEN_CIRCLE

#include "Vector2.hpp"

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
};

#endif//LICHEN_CIRCLE
