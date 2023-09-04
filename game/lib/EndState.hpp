#ifndef LICHEN_ENDSTATE
#define LICHEN_ENDSTATE

#include "../../engine/lib/State.hpp"
#include "../../engine/lib/Timer.hpp"
#include "../../engine/lib/Color.hpp"
#include "../../engine/lib/Music.hpp"


class EndState : public State
{
    private:
        Timer TextColorChange;
        Color TextColor;
        Music* _EndMusic;
        
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update(float);
        void Render();

        void Start();
        void Pause();
        void Resume();

};


#endif//LICHEN_ENDSTATE