#include "../lib/ScreenFade.hpp"

ScreenFade::ScreenFade(GameObject& GameObj, Color FilterColor, float Start, float Finish, float Time)
: Component(GameObj), _FadeFilter(GameObj, FilterColor)
{
    _StartPercent = Start;
    _CurrPercent = Start;
    _FinishPercent = Finish;
    _Finished = false;
    _Time = Time;

    float Diff = _FinishPercent - _StartPercent;
    (Diff > 0 ? _FadeIn = true : _FadeIn = false);
    _Step = Diff/_Time;
    _FadeFilter.FilterColor.A = 255 - 255*_StartPercent;
}

ScreenFade::~ScreenFade()
{
}

void ScreenFade::RedirectFade(float Finish)
{
    _StartPercent = _CurrPercent;
    _FinishPercent = Finish;
    _Finished = false;
    float Diff = _FinishPercent - _StartPercent;
    (Diff > 0 ? _FadeIn = true : _FadeIn = false);
    _Step = Diff/_Time;
}

void ScreenFade::SetTime(float Time)
{
    _Time = Time;
}


bool ScreenFade::Is(std::string Type)
{
    return ("ScreenFade == Type");
}

void ScreenFade::Render()
{
    _FadeFilter.Render();
}

void ScreenFade::Update(float Dt)
{
    if(!_Finished)
    {
        _CurrPercent += _Step*Dt;
        if((_FadeIn && (_CurrPercent > _FinishPercent)) 
        || (!_FadeIn && (_CurrPercent < _FinishPercent)))
        {
            _CurrPercent = _FinishPercent;
            _Finished = true;
        }
        _FadeFilter.FilterColor.A = 255 - 255*_CurrPercent;
        _FadeFilter.Update(Dt);
    }
    
}
