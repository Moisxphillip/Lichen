#include "UserInterface/UIRightBar.hpp"
#include "UserInterface/UIBagMenu.hpp"

UIRightBar::UIRightBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIGroupComponent(ParentComponent, Position){}

void UIRightBar::GroupStart()
{
    LoadImage("res/img/UI/clicker.png");
    // AddComponent(new UIBagButton({}, Vector2(1180,630)));
}