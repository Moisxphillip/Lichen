#include "UserInterface/UIPlayerBar.hpp"
#include <iostream>

// _________________________________________________#UIPlayerBar_________________________________________________
  
UIPlayerBar::UIPlayerBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIGroupComponent(Parent, Controller, Position){}

void UIPlayerBar::Start()
{
    LoadImage("res/img/UI/PlayerBar.png");

    AddComponent(new UILifeBar(Parent, Controller, Vector2(0,0)));
    AddComponent(new UIStaminaBar(Parent, Controller, Vector2(0,0)));
    AddComponent(new UIManaBar(Parent, Controller, Vector2(0,0)));
}


// _________________________________________________#UILifeBar_________________________________________________

UILifeBar::UILifeBar(GameObject& Parent, UIController& Controller, Vector2 Position):UIComponent(Parent, Controller, Position){}

void UILifeBar::Start()
{
    LoadImage("res/img/UI/LifeBar.png");
}

void UILifeBar::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos);
    _CurrentLife = 50.f / 100.f;
}

void UILifeBar::Render()
{
    if(UISprite)
    {
        UISprite->SetClip(0,0,_CurrentLife*UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
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
    UIComponent::Update(Dt, BasePos);
    _CurrentStamina = 1;
}

void UIStaminaBar::Render()
{
    if(UISprite)
    {
        std::cout<<_CurrentStamina<<std::endl;
        UISprite->SetClip(0,0,_CurrentStamina*UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
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
    UIComponent::Update(Dt, BasePos);
    _CurrentMana = 80.f / 100.f;
}

void UIManaBar::Render()
{
    if(UISprite)
    {
        UISprite->SetClip(0,0,_CurrentMana*UISprite->GetWidth(),UISprite->GetHeight());
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
    }
}

