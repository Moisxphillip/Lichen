#ifndef LICHEN_TITLESTATE
#define LICHEN_TITLESTATE

#include "../../engine/lib/Scene.hpp"
#include "../../engine/lib/Timer.hpp"
#include "../../engine/lib/Color.hpp"


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