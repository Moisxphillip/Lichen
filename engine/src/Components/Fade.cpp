#include "Components/Fade.hpp"
#include <algorithm>

Fade::Fade(GameObject& GameObj, Color StartColour, Color FinishColour, float TimeSpan)
: Component(GameObj), _FadeFilter(GameObj, StartColour)
{
    _Start = StartColour;
    _Finish = FinishColour;
    _Limit = TimeSpan;
    _FadeStep.SetLimit(TimeSpan);
    _FadeStep.Restart();
    _Type = ComponentType::Fade;
}

Fade::~Fade()
{
}

void Fade::SetSpan(float Time)
{
    _FadeStep.SetLimit(Time);
    _FadeStep.Restart();
}

void Fade::Render()
{
    _FadeFilter.Render();
}

void Fade::Update(float Dt)
{
    if(!_FadeStep.Finished())
    {
        _FadeStep.Update(Dt);
        _FadeFilter.FilterColor = Color::Interpolation(_Start, _Finish, std::clamp(_FadeStep.Get()/_Limit, 0.0f, 1.0f));
    }    
}

void Fade::SetFinishColor(Color New)
{
    _Start = _FadeFilter.FilterColor;
    _Finish = New;
    _FadeStep.Restart();
}

Color Fade::GetColor()
{
    return _FadeFilter.FilterColor;
}