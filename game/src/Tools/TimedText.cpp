#include "Tools/TimedText.hpp"

TimedText::TimedText(GameObject& Parent, Text* ToPrompt, Color Colour, float FadeIn, float Stay, float FadeOut)
: Component(Parent), _Text(ToPrompt), _TextColor(Colour), _TimeIn(FadeIn), _TimeMiddle(Stay), _TimeOut(FadeOut)
{
    _In = true;
    _Middle = true;
    _PhaseTimer.SetLimit(FadeIn);
}

void TimedText::Update(float Dt)
{
    _PhaseTimer.Update(Dt);
    if (_In)
    {
        float Alpha = (_PhaseTimer.Finished()) ? 1.0f : _PhaseTimer.Get()/_TimeIn;
        _TextColor.a = Alpha;
        _Text->SetColor(_TextColor);
        if (_PhaseTimer.Finished())
        {
            _In = false;
            _PhaseTimer.SetLimit(_TimeMiddle);
            _PhaseTimer.Restart();
        }
    }
    else if (_Middle)
    {
        if (_PhaseTimer.Finished())
        {
            _Middle = false;
            _PhaseTimer.SetLimit(_TimeOut);
            _PhaseTimer.Restart();
        }
    }
    else
    {
        float Alpha = (_PhaseTimer.Finished()) ? 0.0f : 1.0f - _PhaseTimer.Get()/_TimeOut;
        _TextColor.a = Alpha;
        _Text->SetColor(_TextColor);
        if (_PhaseTimer.Finished())
        {
            Parent.RequestDelete();
        }
    }
}

