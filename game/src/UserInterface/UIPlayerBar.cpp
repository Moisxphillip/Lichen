#include "UserInterface/UIPlayerBar.hpp"
#include <iostream>
#include "Character/Player.hpp"

// _________________________________________________#UIPlayerBar_________________________________________________
  
UIPlayerBar::UIPlayerBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIGroupComponent(ParentComponent, Position){}

void UIPlayerBar::GroupStart()
{
    LoadImage("res/img/UI/PlayerBar.png");

    AddComponent(new UILifeBar(weak_from_this(), Vector2(80,12)));
    AddComponent(new UIStaminaBar(weak_from_this(), Vector2(96,62)));
    AddComponent(new UIManaBar(weak_from_this(), Vector2(97,39)));
}


// _________________________________________________#UILifeBar_________________________________________________

UILifeBar::UILifeBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIComponent(ParentComponent, Position){}

void UILifeBar::Start()
{
    LoadImage("res/img/UI/LifeBar65x12.png");
}

void UILifeBar::OnUpdate(Vector2 EventPos, float Dt)
{
    if(Player::Self == nullptr)
    {
        _CurrentLife = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentLife = std::clamp(float(Tmp.HP) / float(Tmp.MaxHP), 0.0f, 1.0f);

    UISprite->SetClip(0,0, std::clamp(_CurrentLife, 0.0f, 1.0f) * UISprite->GetWidth(),UISprite->GetHeight());
}



// _________________________________________________#UIStaminaBar_________________________________________________

UIStaminaBar::UIStaminaBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIComponent(ParentComponent, Position){}

void UIStaminaBar::Start()
{
    LoadImage("res/img/UI/DashBar97x62.png");    
}

void UIStaminaBar::OnUpdate(Vector2 EventPos, float Dt)
{
     if(Player::Self == nullptr)
    {
        _CurrentStamina = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentStamina = std::clamp(float(Tmp.Stamina) / float(Tmp.MaxStamina), 0.0f, 1.0f);
    UISprite->SetClip(0,0,_CurrentStamina*UISprite->GetWidth(),UISprite->GetHeight());
}


// _________________________________________________#UIManaBar_________________________________________________

UIManaBar::UIManaBar(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIComponent(ParentComponent, Position){}

void UIManaBar::Start()
{
    LoadImage("res/img/UI/ManaBar96x39.png");
}

void UIManaBar::OnUpdate(Vector2 EventPos, float Dt)
{
    if(Player::Self == nullptr)
    {
        _CurrentMana = 0.0f;
        return;
    }
    Stats& Tmp = Player::Self->GetStats();
    _CurrentMana = std::clamp(float(Tmp.Mana) / float(Tmp.MaxMana), 0.0f, 1.0f);
    UISprite->SetClip(0,0,_CurrentMana*UISprite->GetWidth(),UISprite->GetHeight());
}



