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
        
        Collider(GameObject&);
        Collider(GameObject&, Vector2, Vector2);
        
        void SetScale(Vector2);
        void SetOffset(Vector2);

        void Render();
        void LateUpdate(float);

};

#endif//LICHEN_COLLIDER