#ifndef LICHEN_BULLET
#define LICHEN_BULLET

#include "../../engine/lib/Component.hpp"


class Bullet : public Component
{
    private:
        Vector2 _Speed;
        float _DistanceLeft;
        int _Damage;
            
    public:
        bool TargetsPlayer;
        Bullet(GameObject&, float, float, int, float, std::string, int, bool, bool);
        int GetDamage();

        void Collided(GameObject&);
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);
};

#endif//LICHEN_BULLET
