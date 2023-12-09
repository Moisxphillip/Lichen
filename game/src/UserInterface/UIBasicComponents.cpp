#include "UserInterface/UIBasicComponents.hpp"
#include "Core/Input.hpp"

UIMoveParent::UIMoveParent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
        std::vector<std::string> Classes)
        :UIGroupComponent(ParentComponent, Position, Classes), _IsHolding(false)
        {}

void UIMoveParent::GroupStart()
{
    Width=248;
    Height=30;
};

void UIMoveParent::OnClick(Vector2 EventPos)
{
    if(!ParentComponent.expired())
    {
        _IsHolding = true;
        _ClickOffset =  EventPos - ParentComponent.lock()->AbsolutePosition;
    }

}

void UIMoveParent::OnLateUpdate(Vector2 EventPos, float Dt){
    if(Input::MouseJustReleased(MouseButton::Left))
    {
        _IsHolding = false;
    }

    if(!ParentComponent.expired() && _IsHolding)
    {
       ParentComponent.lock()->RelativePosition = EventPos - UIController::CurrentUI->Position() - _ClickOffset;
    }
}




UIMovable::UIMovable(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
        std::vector<std::string> Classes)
        :UIGroupComponent(ParentComponent, Position, Classes), IsHolding(false)
        {}

void UIMovable::GroupStart(){};

void UIMovable::OnClick(Vector2 EventPos)
{
    if(!ParentComponent.expired())
    {
        HoldToMouse();
        _ClickOffset =  EventPos - AbsolutePosition;
        
    }

}

void UIMovable::OnLateUpdate(Vector2 EventPos, float Dt){
    if(Input::MouseJustReleased(MouseButton::Left))
    {
        FreeFromMouse();
    }

    if(IsHolding && !ParentComponent.expired())
    {
      RelativePosition = EventPos - ParentComponent.lock()->AbsolutePosition - _ClickOffset;
    }
}

void UIMovable::HoldToMouse()
{
    WantsFocus = true;
    IsHolding = true;

}

void UIMovable::FreeFromMouse()
{
    WantsFocus = false;
    IsHolding = false;
}