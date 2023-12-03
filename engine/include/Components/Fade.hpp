#ifndef LICHEN_SCRFADE
#define LICHEN_SCRFADE

#include "Components/Filter.hpp"
#include "Tools/Timer.hpp"

class Fade : public Component
{
    private:
        Filter _FadeFilter;
        Color _Start;
        Color _Finish;
        Timer _FadeStep;
        float _Limit;

    public:

        Fade(GameObject& Parent, Color StartColour, Color FinishColour, float TimeSpan);
        ~Fade();
        void SetSpan(float TimeSpan);
        void SetFinishColor(Color Colour);
        Color GetColor();

        void Render();
        void Update(float Dt);

};

#endif// LICHEN_SCRFADE