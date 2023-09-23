#ifndef LICHEN_TESTSTATE
#define LICHEN_TESTSTATE

#include "../../engine/lib/Scene.hpp"
#include "../../engine/lib/Timer.hpp"
#include "../../engine/lib/Color.hpp"


class Test01 : public Scene
{
    private:
        Timer TextColorChange;
        Color TextColor;
        
    public:
        Test01();
        ~Test01();

        void LoadAssets();
        void PhysicsUpdate(float);
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//LICHEN_TESTSTATE