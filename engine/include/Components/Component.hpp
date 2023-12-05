#ifndef LICHEN_COMPONENT
#define LICHEN_COMPONENT

#include "Core/GameObject.hpp"
#include "Core/Enum.hpp"

class Component
{
    protected:
        ComponentType _Type;
    public:
        bool Active;
        GameObject& Parent;
        Component(GameObject& Parent);
        virtual ~Component();
        virtual void PhysicsUpdate(float Dt);
        virtual void Update(float Dt);
        virtual void LateUpdate(float Dt);
        virtual void OnCollision(GameObject& Other);
        virtual void Render();
        virtual void Start();
        virtual ComponentType Type();
        bool Is(ComponentType Type);

};

#endif//LICHEN_COMPONENT