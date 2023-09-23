#ifndef LICHEN_STAGESTATE
#define LICHEN_STAGESTATE

#include "../../engine/lib/Scene.hpp"
#include "../../engine/lib/XRand.hpp"

class StageScene : public Scene
{
    private:
        Music *_SceneMusic;
        bool _QuitFade;
        void _FadeOut();
        
    public:
        XrandU64 Rng;

        StageScene();
        ~StageScene();

        void LoadAssets();

        void Start();
        void Pause();
        void Resume();
        void Update(float);
        void Render();

};


#endif//LICHEN_STAGESTATE