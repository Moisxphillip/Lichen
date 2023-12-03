#include "UserInterface/UIPlayerBar.hpp"
#include <iostream>
#include "Character/Player.hpp"

// _________________________________________________#UIPlayerBar_________________________________________________
  
UIPlayerBar::UIPlayerBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIGroupComponent(Parent, Controller, Position){}

void UIPlayerBar::Start()
{
    LoadImage("res/img/UI/PlayerBar.png");

    AddComponent(new UILifeBar(Parent, Controller, RelativePosition + Vector2(52,8)));
    AddComponent(new UIStaminaBar(Parent, Controller, RelativePosition + Vector2(85,56)));
    AddComponent(new UIManaBar(Parent, Controller, RelativePosition + Vector2(83,34)));
}


// _________________________________________________#UILifeBar_________________________________________________

UILifeBar::UILifeBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIComponent(Parent, Controller, Position){}

void UILifeBar::Start()
{
    LoadImage("res/img/UI/LifeBar.png");
}

void UILifeBar::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos+RelativePosition);
    if(Player::Self == nullptr)
    {
        _CurrentLife = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentLife = std::clamp(float(Tmp.HP) / float(Tmp.MaxHP), 0.0f, 1.0f);;
}

void UILifeBar::Render()
{
    if(UISprite)
    {
        UISprite->SetClip(0,0, std::clamp(_CurrentLife, 0.0f, 1.0f) * UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(Parent.Box.Position().x + RelativePosition.x, Parent.Box.Position().y + RelativePosition.y);
    }
}

// _________________________________________________#UIStaminaBar_________________________________________________

UIStaminaBar::UIStaminaBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIComponent(Parent, Controller, Position){}

void UIStaminaBar::Start()
{
    LoadImage("res/img/UI/DashBar.png");    
}

void UIStaminaBar::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos+RelativePosition);
     if(Player::Self == nullptr)
    {
        _CurrentStamina = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentStamina = std::clamp(float(Tmp.Stamina) / float(Tmp.MaxStamina), 0.0f, 1.0f);
}

void UIStaminaBar::Render()
{
    if(UISprite)
    {
        UISprite->SetClip(0,0,_CurrentStamina*UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(Parent.Box.Position().x + RelativePosition.x, Parent.Box.Position().y + RelativePosition.y);
    }
}

// _________________________________________________#UIManaBar_________________________________________________

UIManaBar::UIManaBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIComponent(Parent, Controller, Position){}

void UIManaBar::Start()
{
    LoadImage("res/img/UI/ManaBar.png");
}

void UIManaBar::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos+RelativePosition);
    if(Player::Self == nullptr)
    {
        _CurrentMana = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentMana = std::clamp(float(Tmp.Mana) / float(Tmp.MaxMana), 0.0f, 1.0f);
}

void UIManaBar::Render()
{
    if(UISprite)
    {
        UISprite->SetClip(0,0,_CurrentMana*UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(Parent.Box.Position().x + RelativePosition.x, Parent.Box.Position().y + RelativePosition.y);
    }
}

