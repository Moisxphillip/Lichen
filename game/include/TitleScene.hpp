#ifndef LICHEN_TITLESTATE
#define LICHEN_TITLESTATE

#include "Core/Scene.hpp"
#include "Tools/Timer.hpp"
#include "Tools/Color.hpp"

class TitleScene : public Scene
{
    private:
        Timer TextColorChange;
        Color TextColor;
        
    public:
        TitleScene();
        ~TitleScene();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//LICHEN_TITLESTATE