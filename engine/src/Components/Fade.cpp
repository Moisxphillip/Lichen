#include "Components/Fade.hpp"

Fade::Fade(GameObject& GameObj, Color FilterColor, float Start, float Finish, float Time)
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
    _Type = ComponentType::Fade;
}

Fade::~Fade()
{
}

void Fade::RedirectFade(float Finish)
{
    _StartPercent = _CurrPercent;
    _FinishPercent = Finish;
    _Finished = false;
    float Diff = _FinishPercent - _StartPercent;
    (Diff > 0 ? _FadeIn = true : _FadeIn = false);
    _Step = Diff/_Time;
}

void Fade::SetTime(float Time)
{
    _Time = Time;
}

void Fade::Render()
{
    _FadeFilter.Render();
}

void Fade::Update(float Dt)
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
        _FadeFilter.FilterColor.a = _CurrPercent;
        _FadeFilter.Update(Dt);
    }
    
}

void Fade::SetColor(Color New)
{
    _FadeFilter.FilterColor.r = New.r;
    _FadeFilter.FilterColor.g = New.g;
    _FadeFilter.FilterColor.b = New.b;
    //Doesn't set alpha
}

Color Fade::GetColor()
{
    return _FadeFilter.FilterColor;
}