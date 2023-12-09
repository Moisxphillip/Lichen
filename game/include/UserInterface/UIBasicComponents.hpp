#ifndef LICHEN_UI_BASIC_COMPONENTS
#define LICHEN_UI_BASIC_COMPONENTS

#include "UserInterface/UIComponent.hpp"

class UIMoveParent : public UIGroupComponent {
private:
    bool _IsHolding;
    Vector2 _ClickOffset;
    std::weak_ptr<UIComponent> _UIToMove;

public:
    UIMoveParent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
    std::vector<std::string> Classes);

    virtual void GroupStart();

    void OnClick(Vector2 EventPos);
    void OnLateUpdate(Vector2 EventPos, float Dt);
};

class UIMovable : public UIGroupComponent {
protected:
    
    Vector2 _ClickOffset;
    std::weak_ptr<UIComponent> _UIToMove;

public:
    bool IsHolding;
    UIMovable(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
    std::vector<std::string> Classes);

    virtual void GroupStart();

    virtual void OnClick(Vector2 EventPos);
    void OnLateUpdate(Vector2 EventPos, float Dt);
    void HoldToMouse();
    void FreeFromMouse();
};


#endif