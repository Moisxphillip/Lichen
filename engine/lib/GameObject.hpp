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
        int _Layer;
        std::vector<std::unique_ptr<Component>> _GameObjComponents;

    public:
        Rect Box;
        bool Started;
        float Angle;

        GameObject(int);
        GameObject();
        ~GameObject();

        void Start();
        void PhysicsUpdate(float);
        void Update(float);
        void LateUpdate(float);
        void Collided(GameObject&);
        void Render();
        
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(std::string);
        
        int GetLayer();
        void SetLayer(int);
        // bool operator<(std::shared_ptr<GameObject>&);
        // bool operator<(GameObject&);
};

#endif//LICHEN_GAMEOBJ