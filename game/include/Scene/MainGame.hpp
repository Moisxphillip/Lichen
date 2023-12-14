#ifndef GAME_MAINGAME
#define GAME_MAINGAME

#include "Core/Scene.hpp"
// #include "Tools/Timer.hpp"
// #include "Tools/Color.hpp"

#include <vector>

class MainMap : public Scene
{
    private:
        // Timer TextColorChange;
        // Color TextColor;
        
    public:
        static std::vector<std::vector<int>>* CollisionMap;
        MainMap();
        ~MainMap();

        void LoadAssets();
        void PhysicsUpdate(float);
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};



#endif//GAME_MAINGAME