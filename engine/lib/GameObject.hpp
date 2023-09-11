#ifndef LICHEN_GAMEOBJ
#define LICHEN_GAMEOBJ

//C++ includes
#include <vector>
#include <memory>

//Engine includes
#include "Rectangle.hpp"
#include "Enum.hpp"

class Component;

class GameObject
{
    private:
        bool _GameObjDead;
        int _Layer;
        std::vector<std::unique_ptr<Component>> _GameObjComponents;
        ComponentType _Contains;
        static unsigned int _ID;
        unsigned int _UID;

    public:
        DepthMode Depth;
        Rectangle Box;
        bool Started;
        float Angle;
        CollisionMask Represents, Interacts; 

        GameObject(int);
        GameObject();
        ~GameObject();

        void Start();
        void PhysicsUpdate(float);
        void Update(float);
        void LateUpdate(float);
        void OnCollision(GameObject&);
        void Render();
        
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(ComponentType);
        bool Contains(ComponentType);

        int GetLayer();
        void SetLayer(int);
        int GetUID() const;
        friend std::ostream& operator<<(std::ostream&, const GameObject&);
};

#endif//LICHEN_GAMEOBJ