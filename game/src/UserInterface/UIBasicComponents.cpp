#include "UserInterface/UIBasicComponents.hpp"
#include "Core/Input.hpp"

UIMoveHolder::UIMoveHolder(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
        std::vector<std::string> Classes)
        :UIComponent(ParentComponent, Position, Classes), _IsHolding(false)
        {}

void UIMoveHolder::Start()
{
    LoadImage("res/img/UI/ManaBar.png");
};

void UIMoveHolder::OnClick(Vector2 EventPos)
{
    if(!ParentComponent.expired())
    {
        _IsHolding = true;
        _ClickOffset =  EventPos - ParentComponent.lock()->AbsolutePosition;
    }

}

void UIMoveHolder::OnLateUpdate(Vector2 EventPos, float Dt){
    if(Input::MouseJustReleased(MouseButton::Left))
    {
        _IsHolding = false;
    }

    if(!ParentComponent.expired() && _IsHolding)
    {
       ParentComponent.lock()->RelativePosition = EventPos - UIController::CurrentUI->Position() - _ClickOffset;
    }
}