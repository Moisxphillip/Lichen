#ifndef LICHEN_SCRFADE
#define LICHEN_SCRFADE

#include "ScreenFilter.hpp"
#include "Timer.hpp"

class ScreenFade : public Component
{
    private:
        //SDL_Surface* _FilterSurface;
        ScreenFilter _FadeFilter;
        bool _FadeIn;
        bool _Finished;
        float _StartPercent;
        float _FinishPercent;
        float _CurrPercent;
        float _Step;
        float _Time;

    public:
        Color FilterColor;
        Timer FadeStep;

        ScreenFade(GameObject&, Color, float, float, float);
        ~ScreenFade();
        void RedirectFade(float);
        void SetTime(float);
        
        bool Is(std::string);
        void Render();
        void Update(float);

};

#endif// LICHEN_SCRFADE