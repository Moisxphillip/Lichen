#include "UserInterface/UIItem.hpp"
#include "Core/Input.hpp"

UIItem::UIItem(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, std::shared_ptr<Item> BaseItem): 
    UIMovable(ParentComponent, Position, Classes), _BaseItem(BaseItem),  IsRightClicking(false), Hovering(false), CurrentSlotNumber(-1){}

UIItem::~UIItem()
{
    _BaseItem.reset();
};


void UIItem::GroupStart()
{
    LoadImage(_BaseItem->UISpriteFile);
};

void UIItem::OnClick(Vector2 EventPos)
{
    if(!ParentComponent.expired())
    {
        HoldToMouse();
        _ClickOffset =  EventPos - AbsolutePosition;
        auto BagComponent = UIController::CurrentUI->GetComponentByClass("#Bag");
        auto Bag = std::static_pointer_cast<UIBag>(BagComponent.lock());
        Bag->RemoveFromSlot(this);
    }
}

void UIItem::OnDoubleClick(Vector2 EventPos)
{
    _BaseItem->UseItem();
}

void UIItem::OnRightClick(Vector2 EventPos)
{
    IsRightClicking = true;
    UIController::CurrentUI->AddComponent(new UIItenOptions({}, EventPos-Camera::Position(), {}, this));
}

void UIItem::OnRelease(Vector2 EventPos)
{
    auto BagComponent = UIController::CurrentUI->GetComponentByClass("#Bag");

    if(BagComponent.expired())
    {
        return;
    }

    auto Bag = std::static_pointer_cast<UIBag>(BagComponent.lock());
    if(Bag->IsInside(EventPos))
    {
        Bag->Store(this, EventPos);
    }
    else
    {
        Bag->ThrowFromSlot(this);
    }
}

void UIItem::OnHover(Vector2 EventPos)
{
    if(Hovering || IsHolding)
    {
        return;
    }
    else
    {
        Hovering = true;
        UIController::CurrentUI->AddComponent(new UIItemDescriptor({}, EventPos-Camera::Position(), {}, this));
    }
    
}

std::shared_ptr<Item> UIItem::GetBaseItem()
{
    return _BaseItem;
}

void UIItem::Use()
{
    _BaseItem->UseItem();
}


//________________________________________________________#UIItemDescriptor________________________________________________________

UIItemDescriptor::UIItemDescriptor(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item)
    : UIComponent(ParentComponent, Position, Classes), _Item(Item)
    {

    }

void UIItemDescriptor::Start()
{
    LoadImage("res/img/UI/hovering-back.png");
    UISprite->SetScale(Vector2(1.5,1.5));

    if(!_Item || !_Item->GetBaseItem())
    {
        Close();
        return;
    }

    auto BaseItem = _Item->GetBaseItem();
    // new Text(Parent, "./res/ttf/Caviar.ttf", 20, TextStyle::SOLID, TextLine, TextColor)
    _ItemName = new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, BaseItem->Name, Color("#00ddcb"));
    
    if(BaseItem->IsEquipment())
    {
        auto Stats = std::static_pointer_cast<Equipment>(BaseItem)->GetStats();
        if(Stats.Dex > 0) _StatsDescription.emplace_back(new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, "Destreza: (+"+std::to_string(Stats.Dex) +")",  Color("#2cd000")));
        if(Stats.Int > 0) _StatsDescription.emplace_back(new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, "Inteligência: (+"+std::to_string(Stats.Int) +")",  Color("#2cd000")));
        if(Stats.Str > 0 ) _StatsDescription.emplace_back(new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, "Força: (+"+std::to_string(Stats.Str) +")",  Color("#2cd000")));
        if(Stats.Vit > 0) _StatsDescription.emplace_back(new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, "Vitalidade: (+"+std::to_string(Stats.Vit) +")",  Color("#2cd000")));
    }

    _Description = new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, BaseItem->Description, Color("#c3c3c3"));

    _UseText = new Text(UIController::CurrentUI->Parent, "./res/ttf/Caviar.ttf", 12, TextStyle::SOLID, BaseItem->UseText, Color("#2cd000"));
}
void UIItemDescriptor::OnUpdate(Vector2 EventPos, float Dt)
{
    RelativePosition = EventPos - UIController::CurrentUI->Position()+ Vector2(5,5);

    if(_Item && (_Item->IsRightClicking || _Item->IsHolding || !_Item->IsInside(EventPos)) )
    {
        Close();
        _Item->Hovering = false;
    }
}



void UIItemDescriptor::ComplementaryRender()
{
    _ItemName->Render(AbsolutePosition+Vector2(5,5));
    int Base = 30;
    for(auto Stats : _StatsDescription)
    {
        Stats->Render(AbsolutePosition+Vector2(5,Base));
        Base+=20;
    }
    _Description->Render(AbsolutePosition+Vector2(5,Base));
    // _UseText->Render(AbsolutePosition+Vector2(5,Base+30));
}
//________________________________________________________#UIItenOptions________________________________________________________

UIItenOptions::UIItenOptions(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item):UIGroupComponent(ParentComponent, Position, Classes),_Item(Item){}

void UIItenOptions::GroupStart()
{
    AddComponent(new UIItenOptionUse(weak_from_this(), Vector2(0,0), {}, _Item));
    AddComponent(new UIItenOptionThrow(weak_from_this(), Vector2(0,20), {}, _Item));
    Width=232;
    Height=40;
}

void UIItenOptions::OnUpdate(Vector2 EventPos, float Dt)
{
    Input& InputController = Input::Instance();

    if(!UIComponent::IsInside(InputController.MousePosition(), 50,50))
    {
        _Item->IsRightClicking = false;
        Close();
    }
}

//________________________________________________________#UIItenOptionUse________________________________________________________

UIItenOptionUse::UIItenOptionUse(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item):UIComponent(ParentComponent, Position, Classes),_Item(Item){}

void UIItenOptionUse::Start()
{
    LoadImage("res/img/UI/useui.png", 2, 2, 1);
}

void UIItenOptionUse::OnClick(Vector2 EventPos)
{
    if(_Item)
    {
        _Item->Use();
    }
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

UIItenOptionThrow::UIItenOptionThrow(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes,UIItem* Item):UIComponent(ParentComponent, Position, Classes),_Item(Item){}

void UIItenOptionThrow::Start()
{
    LoadImage("res/img/UI/descartarui.png", 2, 2, 1);
}

void UIItenOptionThrow::OnClick(Vector2 EventPos)
{
    auto BagComponent =  UIController::CurrentUI->GetComponentByClass("#Bag");
    if(_Item && !BagComponent.expired())
    {
        auto Bag =  std::static_pointer_cast<UIBag>(BagComponent.lock());
        Bag->ThrowFromSlot(_Item);
    }
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
