
#include "Tools/DistanceTrigger.hpp"
#include "Character/Player.hpp"

DistanceTrigger::DistanceTrigger(GameObject& Parent, Component* Subject, float MaxDistance, DistTriggerMode Mode)
: Component(Parent), _Subject(Subject), _Mode(Mode), _MaxDistance(MaxDistance*MaxDistance), _Active(true)
{
}

void DistanceTrigger::SetOnActivation(std::function<void()> Activation)
{
    _OnActive = Activation;
}

void DistanceTrigger::SetOnInactivation(std::function<void()> Inactivation)
{
    _OnInactive = Inactivation;
}

bool DistanceTrigger::_OnBounds()
{
    return (Player::Self != nullptr ? _Subject->Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Position()) < _MaxDistance : false);
}

void DistanceTrigger::Start()
{
    // bool Is = _OnBounds();
    // _Active = _Subject->Active ;
}

void DistanceTrigger::Update(float Dt)
{
    if(Player::Self == nullptr)
    {
        return;
    }

    switch(_Mode)
    {
        case DistTriggerMode::Disable:
            if(!_Active && _OnBounds())
            {
                _Subject->Active = true;
                _Active = true;
            }
            else if (_Active && !_OnBounds())
            {
                _Subject->Active = false;
                _Active = false;
            }
            break;
        
        case DistTriggerMode::Enable:
            if(!_Active && _OnBounds())
            {
                _Subject->Active = false;
                _Active = true;
            }
            else if (_Active && !_OnBounds())
            {
                _Subject->Active = true;
                _Active = false;
            }
            break;

        case DistTriggerMode::Delete:
            if(!_OnBounds())
            {
                Parent.RequestDelete();
            }
            break;

        case DistTriggerMode::Custom:
            if(!_Active && _OnBounds())
            {
                _Active = true;
                _OnActive();
            }
            else if (_Active && !_OnBounds())
            {
                _Active = false;
                if(_OnInactive)
                {
                    _OnInactive();
                }
            }
            break;

        default:
            break;
    }
}