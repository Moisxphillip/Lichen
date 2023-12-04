#ifndef LICHEN_UI_BASIC_COMPONENTS
#define LICHEN_UI_BASIC_COMPONENTS

#include "UserInterface/UIComponent.hpp"

class UIMoveHolder : public UIComponent {
private:
    bool _IsHolding;
    Vector2 _ClickOffset;
    std::weak_ptr<UIComponent> _UIToMove;

public:
    UIMoveHolder(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
    std::vector<std::string> Classes);

    virtual void Start();

    void OnClick(Vector2 EventPos);
    void OnLateUpdate(Vector2 EventPos, float Dt);
};

#endif