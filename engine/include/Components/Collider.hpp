#ifndef LICHEN_COLLIDER
#define LICHEN_COLLIDER

#include "Components/Component.hpp"
#include "Math/Vector2.hpp"
#include "Math/Rectangle.hpp"
#include "Graphics/Draw.hpp"

class Collider : public Component
{
    private:
        Vector2 _Scale;
        Vector2 _Offset;
        Draw _Form;

    public:
        Rectangle Box;
        
        Collider(GameObject& Parent);
        Collider(GameObject& Parent, Vector2 Scale, Vector2 Offset);
        
        void SetScale(Vector2 Scale);
        void SetOffset(Vector2 Offset);

        void LateUpdate(float Dt);
        void Render();

};

#endif//LICHEN_COLLIDER