#ifndef LICHEN_STAGESTATE
#define LICHEN_STAGESTATE

#include "../../engine/lib/State.hpp"
#include "../../engine/lib/XRand.hpp"

class StageState : public State
{
    private:
        Music *_StateMusic;
        bool _QuitFade;
        void _FadeOut();
        
    public:
        XrandU64 Rng;

        StageState();
        ~StageState();

        void LoadAssets();

        void Start();
        void Pause();
        void Resume();
        void Update(float);
        void Render();

};


#endif//LICHEN_STAGESTATE