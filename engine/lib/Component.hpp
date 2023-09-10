#ifndef LICHEN_COMPONENT
#define LICHEN_COMPONENT

#include "GameObject.hpp"
#include "Enum.hpp"

class Component
{
    protected:
        GameObject& Parent;
        ComponentType _Type;
    public:
        Component(GameObject&);
        virtual ~Component();
        virtual void PhysicsUpdate(float);
        virtual void Update(float);
        virtual void LateUpdate(float);
        virtual void OnCollision(GameObject&);
        virtual void Render();
        virtual void Start();
        virtual ComponentType Type();
        bool Is(ComponentType);

};

#endif//LICHEN_COMPONENT