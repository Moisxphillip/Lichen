#ifndef LICHEN_MINION
#define LICHEN_MINION

#include "../../engine/lib/Component.hpp"

class Minion : public Component
{
    private:
        std::weak_ptr<GameObject> _AlienCenter;
        float _Arc;

    public:
        Minion(GameObject&, std::weak_ptr<GameObject>, float);
        void Shoot(Vector2);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//LICHEN_MINION
