#ifndef LICHEN_PENGCANNON
#define LICHEN_PENGCANNON

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"

class PenguinCannon : public Component
{
    private:
        std::weak_ptr<GameObject> _Body;
        Timer _Cooldown;
    public:
        PenguinCannon(GameObject&, std::weak_ptr<GameObject>);
        void Shoot();

        void Render();
        void Start();
        void Update(float);

};

#endif//LICHEN_PENGCANNON