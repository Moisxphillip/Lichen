#ifndef LICHEN_TITLESTATE
#define LICHEN_TITLESTATE

#include "../../engine/lib/State.hpp"
#include "../../engine/lib/Timer.hpp"
#include "../../engine/lib/Color.hpp"


class TitleState : public State
{
    private:
        Timer TextColorChange;
        Color TextColor;
        
    public:
        TitleState();
        ~TitleState();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//LICHEN_TITLESTATE