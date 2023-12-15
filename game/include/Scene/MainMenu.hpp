#ifndef GAME_MAINMENU
#define GAME_MAINMENU

#include "Core/Scene.hpp"
#include "Tools/Timer.hpp"

class MainMenu : public Scene
{
    private:
        Timer ToPlay;
        bool Starting;
        // Color TextColor;
        
    public:
        MainMenu();
        ~MainMenu();

        void LoadAssets();
        void PhysicsUpdate(float);
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};



#endif//GAME_MAINMENU