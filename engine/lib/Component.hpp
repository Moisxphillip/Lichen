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
        virtual void Update(float);
        virtual void PhysicsUpdate(float);
        virtual void Collided(GameObject&);
        virtual void Render();
        virtual void Start();
        virtual bool Is(std::string);
        virtual bool Is(ComponentType);

};

#endif//LICHEN_COMPONENT