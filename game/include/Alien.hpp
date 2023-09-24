#ifndef LICHEN_ALIEN
#define LICHEN_ALIEN

#include "Components/Component.hpp"
#include "Tools/Timer.hpp"
#include "Tools/XRand.hpp"

class Alien : public Component
{
    private:
        enum AlienState
        {
            MOVING,
            REST            
        };
        AlienState _CurrState;

        Timer _Rest;
        Vector2 Destination;
        Vector2 _Speed;
        int _HP;
        int _NumMinions;
        std::vector<std::weak_ptr<GameObject>> _MinionVec;
        XrandF32 _WaitTime;
        float _ExtraTime;

    public:
        static int AlienCount;
        Alien(GameObject&, int);
        ~Alien();
        
        void OnCollision(GameObject&);
        void Render();
        void Start();
        void Update(float);

};


#endif//LICHEN_ALIEN