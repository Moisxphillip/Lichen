#include "UserInterface/UIBagMenu.hpp"
#include "UserInterface/UIBagMenu.hpp"
#include "Core/Input.hpp"
#include <iostream>

  
  
UIBagButton::UIBagButton(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position):UIComponent(ParentComponent, Position),_IsOpened(false){}

void UIBagButton::Start(){
    LoadImage("res/img/UI/mochilaui.png");
}

void UIBagButton::OnRelease(Vector2 EventPos){
    auto Bag = UIController::CurrentUI->GetComponentByClass("#Bag");
    if (!Bag.expired())
    {
        Bag.lock().get()->Close();
    }
    else
    {
        UIController::CurrentUI->AddComponent(new UIBag({}, UIBag::LastBagRelativePosition, {"#Bag"}));
    }
}

//________________________________________________________#UIBag________________________________________________________

Vector2 UIBag::LastBagRelativePosition = Vector2(600,100);

UIBag::UIBag(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIGroupComponent(ParentComponent, Position, Classes){}

void UIBag::GroupStart()
{
    LoadImage("res/img/UI/bag.png");
    AddComponent(new UIMoveHolder(weak_from_this(), Vector2(0,0), {}));
    AddComponent(new UIBagClose(weak_from_this(), Vector2(220,5), {"#Close"}));
}

void UIBag::Close()
{
    UIBag::LastBagRelativePosition = RelativePosition;
    UIComponent::Close();
}

void UIBag::OnRightClick(Vector2 EventPos)
{
    UIController::CurrentUI->AddComponent(new UIItenOptions({}, EventPos-Camera::Position(), {}));
}

void UIBag::OnLateUpdate(Vector2 EventPos, float Dt)
{
    for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
    {
        if ((*Component)->ShouldBeClosed() && (*Component)->HasClass("#Close"))
        {
            Close();
            return;
        }
    }
}

// std::vector<std::map<Vector2, UIItem*>> InventorySlots;
bool UIBag::StoreAtSlot(UIItem* Item, Vector2 EventPos)
{
    // for(auto Row : InventorySlots)
    // {
    //     for(auto Column : Row)
    //     {
    //         if(Rectangle(Column.first.x, Column.first.y, SLOT_WIDTH, SLOT_HEIGHT).Contains(EventPos))
    //         {
    //             if(Column.second == nullptr)
    //             {
    //                 // Inventory->StoreAt();
    //                 // Item->RelativePosition = Column.first;
    //                 return true;
    //             }
    //             else 
    //             {
    //                 // Item* =  Inventory->RemoveAt();
    //                 // Inventory->StoreAt(Item->BaseItem);

    //                 // Inventory->StoreAt();
    //                 return true;
    //             }
                
    //         }
    //     }
    // }
    // return false;
}


//________________________________________________________#UIBagClose________________________________________________________

UIBagClose::UIBagClose(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIComponent(ParentComponent, Position, Classes){}

void UIBagClose::Start()
{
    LoadImage("res/img/UI/closeui.png");
}

void UIBagClose::OnClick(Vector2 EventPos)
{
   Close();
}

//________________________________________________________#UIItenOptions________________________________________________________

UIItenOptions::UIItenOptions(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIGroupComponent(ParentComponent, Position, Classes){}

void UIItenOptions::GroupStart()
{
    AddComponent(new UIItenOptionUse(weak_from_this(), Vector2(0,0), {}));
    AddComponent(new UIItenOptionThrow(weak_from_this(), Vector2(0,20), {}));
    Width=232;
    Height=40;
}

void UIItenOptions::OnUpdate(Vector2 EventPos, float Dt)
{
    Input& InputController = Input::Instance();

    if(!UIComponent::IsInside(InputController.MousePosition(), 50,50))
    {
        Close();
    }
}

//________________________________________________________#UIItenOptionUse________________________________________________________

UIItenOptionUse::UIItenOptionUse(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIComponent(ParentComponent, Position, Classes){}

void UIItenOptionUse::Start()
{
    LoadImage("res/img/UI/useui.png", 2, 2, 1);
}

void UIItenOptionUse::OnHover(Vector2 EventPos)
{
    UISprite->SetFrame(1);
}

void UIItenOptionUse::OnUpdate(Vector2 EventPos, float Dt)
{
    Input InputController = Input::Instance();

    if(!IsInside(InputController.MousePosition()))
    {
        UISprite->SetFrame(0);
    }
}

//________________________________________________________#UIItenOptionThrow________________________________________________________

UIItenOptionThrow::UIItenOptionThrow(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIComponent(ParentComponent, Position, Classes){}

void UIItenOptionThrow::Start()
{
    LoadImage("res/img/UI/descartarui.png", 2, 2, 1);
}

void UIItenOptionThrow::OnHover(Vector2 EventPos)
{
    UISprite->SetFrame(1);
}

void UIItenOptionThrow::OnUpdate(Vector2 EventPos, float Dt)
{
    Input InputController = Input::Instance();

    if(!IsInside(InputController.MousePosition()))
    {
        UISprite->SetFrame(0);
    }
}



