#ifndef LICHEN_GAMEOBJ
#define LICHEN_GAMEOBJ

//C++ includes
#include <vector>
#include <memory>

//Engine includes
#include "Rect.hpp"

class Component;

class GameObject
{
    private:
        bool _GameObjDead;
        std::vector<std::unique_ptr<Component>> _GameObjComponents;

    public:
        Rect Box;
        bool Started;
        float Angle;

        GameObject();
        ~GameObject();

        void Start();
        void Update(float);
        void PhysicsUpdate(float);
        void Collided(GameObject&);
        void Render();
        
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(std::string);
        
};

#endif//LICHEN_GAMEOBJ