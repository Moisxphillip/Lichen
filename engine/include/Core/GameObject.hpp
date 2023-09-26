#ifndef LICHEN_GAMEOBJ
#define LICHEN_GAMEOBJ

//C++ includes
#include <vector>
#include <memory>

//Engine includes
#include "Math/Rectangle.hpp"
#include "Core/Enum.hpp"

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

        GameObject(int Layer);
        GameObject();
        ~GameObject();

        void Start();
        void PhysicsUpdate(float Dt);
        void Update(float Dt);
        void LateUpdate(float Dt);
        void OnCollision(GameObject& Other);
        void Render();
        
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* Add);
        void RemoveComponent(Component* Remove);
        Component* GetComponent(ComponentType Type);
        bool Contains(ComponentType Type);

        int GetLayer();
        void SetLayer(int NewLayer);
        int GetUID() const;
        friend std::ostream& operator<<(std::ostream& O, const GameObject& Object);
};

#endif//LICHEN_GAMEOBJ