#ifndef LICHEN_AABB
#define LICHEN_AABB


struct TestRect
{
    float x, y, w, h;
    bool Rigid, Stationary;
    float Mass;
};

struct TestCircle
{
    float x, y, r;
    bool Rigid, Stationary;
    float Mass;
};

class AABB 
{
    public:
        static bool CheckAndResolve(TestRect&, TestRect&);
        static bool CheckAndResolve(TestCircle&, TestCircle&);
        static bool CheckAndResolve(TestRect&, TestCircle&);
};

#endif//LICHEN_AABBCOLLISION