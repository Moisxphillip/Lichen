#ifndef LICHEN_COMPONENT
#define LICHEN_COMPONENT

#include "GameObject.hpp"
#include "Settings.hpp"

class Component
{
    protected:
        GameObject& GameObjAssoc;

    public:
        Uses ComponentFlags;
        Component(GameObject&);
        virtual ~Component();
        virtual void Update(float);
        virtual void Collided(GameObject&);
        virtual void Render();
        virtual void Start();
        virtual bool Is(std::string);

};

#endif//LICHEN_COMPONENT