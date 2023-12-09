#ifndef LICHEN_UI_PLAYER_BAR
#define LICHEN_UI_PLAYER_BAR

#include "UserInterface/UIComponent.hpp"

class UIPlayerBar : public UIGroupComponent {
public:
    UIPlayerBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);

    void GroupStart();
};

class UILifeBar : public UIComponent {
private:
    float _CurrentLife;
public:
    UILifeBar(std::weak_ptr<UIComponent> ParentComponent,  Vector2 Position);

    void OnUpdate(Vector2 EventPos, float Dt);
    void Start();
};

class UIStaminaBar : public UIComponent {
private:
    float _CurrentStamina;
public:
    UIStaminaBar(std::weak_ptr<UIComponent> ParentComponent,  Vector2 Position);

    void OnUpdate(Vector2 EventPos, float Dt);
    void Start();
};

class UIManaBar : public UIComponent {
private:
    float _CurrentMana;
public:
    UIManaBar(std::weak_ptr<UIComponent> ParentComponent,  Vector2 Position);

    void OnUpdate(Vector2 EventPos, float Dt);
    void Start();
};

#endif