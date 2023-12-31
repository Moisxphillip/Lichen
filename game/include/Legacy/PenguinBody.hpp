#ifndef LICHEN_PENGBODY
#define LICHEN_PENGBODY

#include "Components/Component.hpp"

class PenguinBody : public Component
{
    private:
        std::weak_ptr<GameObject> _Cannon;
        Vector2 _Speed;
        float _LinearSpeed;
        int _HP;

    public:
        static PenguinBody* Self;

        PenguinBody(GameObject&);
        ~PenguinBody();
        Vector2 CurrPosition();

        void OnCollision(GameObject&);
        void Render();
        void Start();
        void Update(float);

};

#endif//LICHEN_PENGBODY