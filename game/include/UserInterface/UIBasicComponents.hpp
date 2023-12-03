#ifndef LICHEN_UI_BASIC_COMPONENTS
#define LICHEN_UI_BASIC_COMPONENTS

#include "UserInterface/UIComponent.hpp"

class UIMoveHolder : public UIComponent {
private:
    Vector2 ClickOffset;
    std::weak_ptr<UIComponent> UIToMove;

public:
    UIMoveHolder(GameObject& Parent, UIController& Controller, Vector2 Position,
        std::vector<std::string> Classes, std::weak_ptr<UIComponent> UIToMove)
        :UIComponent(Parent, Controller, Position, Classes), UIToMove(UIToMove){}

    virtual void Start(Vector2 StartPos){
        Width = 248;
        Height = 50;
    };

    void OnClick(Vector2 EventPos){
        if(!UIToMove.expired())
        {
            ClickOffset =  EventPos - (Parent.Box.Position() + UIToMove.lock().get()->RelativePosition);
        }
    }

    void OnHold(Vector2 EventPos){
        if(!UIToMove.expired())
        {
            UIToMove.lock().get()->RelativePosition = EventPos - Parent.Box.Position() - ClickOffset;
        }
    }
};

#endif