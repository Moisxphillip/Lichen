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

        Fade(GameObject&, Color, float, float, float);
        ~Fade();
        void RedirectFade(float);
        void SetTime(float);
        void SetColor(Color);
        Color GetColor();

        void Render();
        void Update(float);

};

#endif// LICHEN_SCRFADE