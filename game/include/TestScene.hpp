#ifndef LICHEN_TESTSTATE
#define LICHEN_TESTSTATE

#include "Core/Scene.hpp"
#include "Tools/Timer.hpp"
#include "Tools/Color.hpp"

#include <vector>


class Test01 : public Scene
{
    private:
        Timer TextColorChange;
        Color TextColor;
        
    public:
        static std::vector<std::vector<int>>* CollisionMap;
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