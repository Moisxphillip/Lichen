#ifndef LICHEN_COLLIDER
#define LICHEN_COLLIDER

#include "Component.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

class Collider : public Component
{
    private:
        Vector2 _Scale;
        Vector2 _Offset;

    public:
        Rect Box;
        
        Collider(GameObject&);
        Collider(GameObject&, Vector2, Vector2);
        
        void SetScale(Vector2);
        void SetOffset(Vector2);

        bool Is(std::string);
        void Render();
        void LateUpdate(float);

};

#endif//LICHEN_COLLIDER