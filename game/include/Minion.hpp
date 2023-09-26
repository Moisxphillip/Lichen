#ifndef LICHEN_MINION
#define LICHEN_MINION

#include "Components/Component.hpp"

class Minion : public Component
{
    private:
        std::weak_ptr<GameObject> _AlienCenter;
        float _Arc;

    public:
        Minion(GameObject&, std::weak_ptr<GameObject>, float);
        void Shoot(Vector2);
        void Render();
        void Start();
        void Update(float);

};

#endif//LICHEN_MINION
