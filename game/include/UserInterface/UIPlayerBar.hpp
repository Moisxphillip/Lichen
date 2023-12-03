#ifndef LICHEN_UI_PLAYER_BAR
#define LICHEN_UI_PLAYER_BAR

#include "UserInterface/UIComponent.hpp"

class UIPlayerBar : public UIGroupComponent {
public:
    UIPlayerBar(GameObject& Parent, UIController& Controller, Vector2 Position);

    void Start();
};

class UILifeBar : public UIComponent {
private:
    float _CurrentLife;
public:
    UILifeBar(GameObject& Parent, UIController& Controller, Vector2 Position);

    void Update(float Dt, Vector2 BasePos);
    void Start();
    void Render();
};

class UIStaminaBar : public UIComponent {
private:
    float _CurrentStamina;
public:
    UIStaminaBar(GameObject& Parent, UIController& Controller, Vector2 Position);

    void Update(float Dt, Vector2 BasePos);
    void Start();
    void Render();
};

class UIManaBar : public UIComponent {
private:
    float _CurrentMana;
public:
    UIManaBar(GameObject& Parent, UIController& Controller, Vector2 Position);

    void Update(float Dt, Vector2 BasePos);
    void Start();
    void Render();
};

#endif