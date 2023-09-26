#ifndef LICHEN_ENDSTATE
#define LICHEN_ENDSTATE

#include "Core/Scene.hpp"
#include "Core/Music.hpp"
#include "Tools/Color.hpp"
#include "Tools/Timer.hpp"


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