#include "UserInterface/UIBagMenu.hpp"
#include "Core/Input.hpp"
#include <iostream>

  
  
UIBagButton::UIBagButton(GameObject& Parent, UIController& Controller, Vector2 Position):UIComponent(Parent, Controller, Position),_IsOpened(false){}

void UIBagButton::Start(){
    LoadImage("res/img/UI/mochilaui.png");
}

void UIBagButton::OnRelease(Vector2 EventPos){
    auto Bag = Controller.GetComponentByClass("#Bag");
    if (!Bag.expired())
    {
        Bag.lock().get()->Close();
    }
    else
    {
        Controller.AddComponent(new UIBag(Parent, Controller, UIBag::LastBagRelativePosition, {"#Bag"}));
    }
}

//________________________________________________________#UIBag________________________________________________________

Vector2 UIBag::LastBagRelativePosition = Vector2(600,100);

UIBag::UIBag(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIGroupComponent(Parent, Controller, Position, Classes){}

void UIBag::Start()
{
    LoadImage("res/img/UI/bag.png");
    AddComponent(new UIMoveHolder(Parent, Controller, Vector2(0,0), {}, weak_from_this()));
    AddComponent(new UIBagClose(Parent, Controller, RelativePosition+Vector2(220,5), {"#Close"}));
}

void UIBag::Close()
{
    UIBag::LastBagRelativePosition = RelativePosition;
    UIComponent::Close();
}

void UIBag::OnRightClick(Vector2 EventPos)
{
    Controller.AddComponent(new UIItenOptions(Parent,Controller, EventPos-Camera::Position(), {}));
}

void UIBag::LateUpdate(float Dt)
{
    for(auto Component : _UIComponents)
    {
        Component->LateUpdate(Dt);
    }

    for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
    {
        if ((*Component)->ShouldBeClosed() && (*Component)->HasClass("#Close"))
        {
            Close();
            return;
        }
    }
}

//________________________________________________________#UIBagClose________________________________________________________

UIBagClose::UIBagClose(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIComponent(Parent, Controller, Position, Classes){}

void UIBagClose::Start()
{
    LoadImage("res/img/UI/closeui.png");
}

void UIBagClose::OnClick(Vector2 EventPos)
{
   Close();
}

//________________________________________________________#UIItenOptions________________________________________________________

UIItenOptions::UIItenOptions(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIGroupComponent(Parent, Controller, Position, Classes){}

void UIItenOptions::Start()
{
    AddComponent(new UIItenOptionUse(Parent, Controller, RelativePosition, {}));
    AddComponent(new UIItenOptionThrow(Parent, Controller, RelativePosition+Vector2(0,20), {}));
    Width=232;
    Height=40;
}

bool UIItenOptions::IsInside(Vector2 EventPos)
{

    if(EventPos.x >= Parent.Box.x+RelativePosition.x-50 &&
        EventPos.x <Parent.Box.x+RelativePosition.x+50 + Width &&
        EventPos.y >= Parent.Box.y+RelativePosition.y-50  && 
        EventPos.y < Parent.Box.y+RelativePosition.y+50 + Height 
    )
    {
        return true;
    }
    return false;
}

void UIItenOptions::Update(float Dt, Vector2 BasePos)
{
    UIGroupComponent::Update(Dt, BasePos+RelativePosition);
    Input& InputController = Input::Instance();


    if(!IsInside(InputController.MousePosition()))
    {
        Close();
    }
}

//________________________________________________________#UIItenOptionUse________________________________________________________

UIItenOptionUse::UIItenOptionUse(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIComponent(Parent, Controller, Position, Classes){}

void UIItenOptionUse::Start()
{
    LoadImage("res/img/UI/useui.png", 2, 2, 1);
}

void UIItenOptionUse::OnHover(Vector2 EventPos)
{
    UISprite->SetFrame(1);
}

void UIItenOptionUse::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos+RelativePosition);
    Input InputController = Input::Instance();


    if(!IsInside(InputController.MousePosition()))
    {
        UISprite->SetFrame(0);
    }
}

//________________________________________________________#UIItenOptionThrow________________________________________________________

UIItenOptionThrow::UIItenOptionThrow(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIComponent(Parent, Controller, Position, Classes){}

void UIItenOptionThrow::Start(){
    LoadImage("res/img/UI/descartarui.png", 2, 2, 1);
}

void UIItenOptionThrow::OnHover(Vector2 EventPos){
    UISprite->SetFrame(1);
}

void UIItenOptionThrow::Update(float Dt, Vector2 BasePos)
{
    UIComponent::Update(Dt, BasePos+RelativePosition);
    Input InputController = Input::Instance();

    if(!IsInside(InputController.MousePosition()))
    {
        UISprite->SetFrame(0);
    }
}



