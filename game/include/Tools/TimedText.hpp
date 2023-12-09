#ifndef GAME_TIMEDTEXT
#define GAME_TIMEDTEXT

#include "Components/Text.hpp"
#include "Tools/Timer.hpp"

class TimedText : public Component
{
    private:
        Text* _Text;
        Timer _PhaseTimer;
        bool _In, _Middle;
        float _TimeIn, _TimeMiddle, _TimeOut;
        Color _TextColor;

    public:
        TimedText(GameObject& Parent, Text* ToPrompt, Color Colour , float FadeIn, float Stay, float FadeOut);
        void Update(float Dt);
};

#endif//GAME_TIMEDTEXT