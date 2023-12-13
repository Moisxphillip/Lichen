#include "Tools/ActiveArea.hpp"
#include "Character/Player.hpp"

ActiveArea::ActiveArea(GameObject& Parent, Rectangle CoveredArea)
: Component(Parent), _Active(false)
{
    Parent.Box = CoveredArea;
}

void ActiveArea::SetOnActivation(std::function<void()> Activation)
{
    _OnActive = Activation;
}

void ActiveArea::SetOnInactivation(std::function<void()> Inactivation)
{
    _OnInactive = Inactivation;
}


void ActiveArea::Update(float Dt)
{
    if(Player::Self == nullptr)
    {
        return;
    }


    if(!_Active && Parent.Box.Contains(Player::Self->Parent.Box.Center()))
    {
        if(_OnActive)
        {
            _OnActive();
        }
        _Active = true;
    }
    else if (_Active && !Parent.Box.Contains(Player::Self->Parent.Box.Center()))
    {
        if(_OnInactive)
        {
            _OnInactive();
        }
        _Active = false;
    }
}