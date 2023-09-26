#ifndef LICHEN_SCRFADE
#define LICHEN_SCRFADE

#include "Components/Filter.hpp"
#include "Tools/Timer.hpp"

class Fade : public Component
{
    private:
        Filter _FadeFilter;
        bool _FadeIn;
        bool _Finished;
        float _StartPercent;
        float _FinishPercent;
        float _CurrPercent;
        float _Step;
        float _Time;

    public:
        Timer FadeStep;

        Fade(GameObject& Parent, Color Colour, float StartPercent, float FinishPercent, float TimeSpan);
        ~Fade();
        void RedirectFade(float FinishPercent);
        void SetTime(float TimeSpan);
        void SetColor(Color Colour);
        Color GetColor();

        void Render();
        void Update(float Dt);

};

#endif// LICHEN_SCRFADE