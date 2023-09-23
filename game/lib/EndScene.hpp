#ifndef LICHEN_ENDSTATE
#define LICHEN_ENDSTATE

#include "../../engine/lib/Scene.hpp"
#include "../../engine/lib/Timer.hpp"
#include "../../engine/lib/Color.hpp"
#include "../../engine/lib/Music.hpp"


class EndScene : public Scene
{
    private:
        Timer TextColorChange;
        Color TextColor;
        Music* _EndMusic;
        
    public:
        EndScene();
        ~EndScene();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//LICHEN_ENDSTATE