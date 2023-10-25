#include "Tools/Controls.hpp"
#include "Core/Input.hpp"

std::map<GameControls, std::vector< std::pair<ControlCheck, int> > > Controls::_Control;

Controls::Controls()
{
    //Define redundant controls using pushbacks
    _Control[GameControls::Up].push_back(std::make_pair(ControlCheck::Key, static_cast<int>(Key::W)));
    _Control[GameControls::Down].push_back(std::make_pair(ControlCheck::Key, static_cast<int>(Key::S)));
    _Control[GameControls::Left].push_back(std::make_pair(ControlCheck::Key, static_cast<int>(Key::A)));
    _Control[GameControls::Right].push_back(std::make_pair(ControlCheck::Key, static_cast<int>(Key::D)));

    _Control[GameControls::Dash].push_back(std::make_pair(ControlCheck::Key, static_cast<int>(Key::Space)));
    _Control[GameControls::Attack].push_back(std::make_pair(ControlCheck::MouseButton, static_cast<int>(MouseButton::Left)));
    _Control[GameControls::Special].push_back(std::make_pair(ControlCheck::MouseButton, static_cast<int>(MouseButton::Right)));

}

bool Controls::IsPressed(GameControls Action)
{
    bool Result = false;

    if(!_Control.count(Action))
    {
        return false;
    }

    std::vector<std::pair<ControlCheck, int>>& Inputs = _Control[Action];
    for(int i = 0; i< (int)Inputs.size(); i++)
    {
        switch(Inputs[i].first)
        {
            case ControlCheck::MouseButton:
                Result = Result || Input::Instance().MousePressedDown(static_cast<MouseButton>(Inputs[i].second));
                break;
            case ControlCheck::Key:
                Result = Result || Input::Instance().KeyPressedDown(static_cast<Key>(Inputs[i].second));
                break;
            case ControlCheck::ControllerButton:
                Result = Result || Input::Instance().ControllerButtonPressedDown(static_cast<ControllerButton>(Inputs[i].second));
                break;
        }
    }
    return Result;
}

bool Controls::IsJustPressed(GameControls Action)
{
    bool Result = false;

    if(!_Control.count(Action))
    {
        return false;
    }

    std::vector<std::pair<ControlCheck, int>>& Inputs = _Control[Action];
    for(int i = 0; i< (int)Inputs.size(); i++)
    {
        switch(Inputs[i].first)
        {
            case ControlCheck::MouseButton:
                Result = Result || Input::Instance().MouseJustPressed(static_cast<MouseButton>(Inputs[i].second));
                break;
            case ControlCheck::Key:
                Result = Result || Input::Instance().KeyJustPressed(static_cast<Key>(Inputs[i].second));
                break;
            case ControlCheck::ControllerButton:
                Result = Result || Input::Instance().ControllerButtonJustPressed(static_cast<ControllerButton>(Inputs[i].second));
                break;
        }
    }
    return Result;
}

bool Controls::IsReleased(GameControls Action)
{
    bool Result = false;

    if(!_Control.count(Action))
    {
        return false;
    }

    std::vector<std::pair<ControlCheck, int>>& Inputs = _Control[Action];
    for(int i = 0; i< (int)Inputs.size(); i++)
    {
        switch(Inputs[i].first)
        {
            case ControlCheck::MouseButton:
                Result = Result || Input::Instance().MouseReleased(static_cast<MouseButton>(Inputs[i].second));
                break;
            case ControlCheck::Key:
                Result = Result || Input::Instance().KeyReleased(static_cast<Key>(Inputs[i].second));
                break;
            case ControlCheck::ControllerButton:
                Result = Result || Input::Instance().ControllerButtonReleased(static_cast<ControllerButton>(Inputs[i].second));
                break;
        }
    }
    return Result;
}

bool Controls::IsJustReleased(GameControls Action)
{
    bool Result = false;

    if(!_Control.count(Action))
    {
        return false;
    }

    std::vector<std::pair<ControlCheck, int>>& Inputs = _Control[Action];
    for(int i = 0; i< (int)Inputs.size(); i++)
    {
        switch(Inputs[i].first)
        {
            case ControlCheck::MouseButton:
                Result = Result || Input::Instance().MouseJustReleased(static_cast<MouseButton>(Inputs[i].second));
                break;
            case ControlCheck::Key:
                Result = Result || Input::Instance().KeyJustReleased(static_cast<Key>(Inputs[i].second));
                break;
            case ControlCheck::ControllerButton:
                Result = Result || Input::Instance().ControllerButtonJustReleased(static_cast<ControllerButton>(Inputs[i].second));
                break;
        }
    }
    return Result;
}

Vector2 Controls::GetAxes()
{
    return Vector2(Input::Instance().GetControllerAxis(ControllerAxis::LeftX), Input::Instance().GetControllerAxis(ControllerAxis::LeftY));
}