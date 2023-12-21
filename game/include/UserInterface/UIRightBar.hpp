#ifndef LICHEN_UI_RIGHT_BAR
#define LICHEN_UI_RIGHT_BAR

#include "UserInterface/UIComponent.hpp"

class UIRightBar : public UIGroupComponent {
public:
    UIRightBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);
    void GroupStart();
};

#endif