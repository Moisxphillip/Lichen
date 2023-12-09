#include "UserInterface/UIBagMenu.hpp"
#include "Mechanics/Inventory.hpp"
#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Character/Player.hpp"
#include <iostream>


Vector2 UIBag::LastBagRelativePosition = Vector2(600,100);

UIBag::UIBag(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIGroupComponent(ParentComponent, Position, Classes)
{

    int i;
    for(int i = 0; i < SLOTS_ROWS; i++)
    {
        std::vector<SlotSpace> Row = {};
        for(int j = 0; j < SLOTS_COLUMNS; j++)
        {
            Row.emplace_back(SlotSpace{i*SLOTS_COLUMNS+j, nullptr, Vector2(INVENTORY_START_WIDTH+SLOT_WIDTH*j, INVENTORY_START_HEIGHT+SLOT_HEIGHT*i), ItemClass::General});
        }
        InventorySlots.emplace_back(Row);
    }

    int total  = SLOTS_COLUMNS*SLOTS_ROWS;

    
    EquipSlot.emplace_back(SlotSpace{total++,nullptr, Vector2(84, 104), ItemClass::Bracelet});
    EquipSlot.emplace_back(SlotSpace{total++,nullptr, Vector2(146, 43), ItemClass::Collar});
    EquipSlot.emplace_back(SlotSpace{total++,nullptr, Vector2(146, 104), ItemClass::Legs});
    EquipSlot.emplace_back(SlotSpace{total++, nullptr, Vector2(146, 166), ItemClass::Boot});
}

UIBag::~UIBag()
{

    for (auto Row = rbegin(InventorySlots); Row != rend(InventorySlots); ++Row) 
    {
        for (auto Slot = rbegin(*Row); Slot != rend(*Row); ++Slot) 
        {
            Slot->Item = nullptr;
        }
    }
    
}

void UIBag::GroupStart()
{
    LoadImage("res/img/UI/bag.png");
    AddComponent(new UIMovable(weak_from_this(), Vector2(0,0), {}));
    AddComponent(new UIBagClose(weak_from_this(), Vector2(220,5), {"#Close"}));

    int i = 0;
    for(auto Row : Inventory::Instance->GetItemInventory())
    {
        int j = 0;
        for(auto Item : Row)
        {
            if(Item != nullptr)
            {
                InventorySlots[i][j].Item = new UIItem(weak_from_this(), InventorySlots[i][j].Position, {}, Item);
                InventorySlots[i][j].Item->CurrentSlotNumber = InventorySlots[i][j].Id;
                AddComponent(InventorySlots[i][j].Item);
            }
            j++;
        }
        i++;
    }

}

void UIBag::Close()
{
    UIBag::LastBagRelativePosition = RelativePosition;
    UIComponent::Close();
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
 
    int idx;
    for(int i = 0; i< (int)(_UIComponents.size()); i++)
	{
		if(_UIComponents[i]->WantsFocus)
		{
            _UIComponents[i]->WantsFocus = false;
            idx = i;
            auto it = _UIComponents.begin() + idx;
            std::rotate(it, it + 1, _UIComponents.end());
            break;
		}
	}
    

}

void UIBag::PlaceAtSlot(SlotSpace& SlotToPlace, UIItem* Item)
{
    std::cout<<"Putting "<<Item->GetBaseItem()->Name<<" from "<<SlotToPlace.Id<<std::endl;

    if(SlotToPlace.SlotType == ItemClass::General)
    {
        int Row = SlotToPlace.Id / SLOTS_COLUMNS;
        int Column = SlotToPlace.Id % SLOTS_COLUMNS;
        Inventory::Instance->StoreAt(Item->GetBaseItem(), Row ,Column );
    }
    else
    {
        if(!Item->GetBaseItem()->IsEquipment()) 
        {
            return;
        }
        Inventory::Instance->Equip(std::static_pointer_cast<Equipment>(Item->GetBaseItem()));
    }

    SlotToPlace.Item = Item;
    Item->CurrentSlotNumber = SlotToPlace.Id;
    Item->RelativePosition = SlotToPlace.Position;

}


void UIBag::RemoveFromSlot(UIItem* Item)
{


    auto& Slot = GetSlot(Item->CurrentSlotNumber);
    std::cout<<"Removing "<<Item->GetBaseItem()->Name<<" from "<<Slot.Id<<std::endl;
    if( Slot.SlotType == ItemClass::General)
    {
        int Row = (Slot.Position.x - INVENTORY_START_WIDTH)/SLOT_WIDTH;
        int Column = (Slot.Position.y - INVENTORY_START_HEIGHT)/SLOT_HEIGHT;
        Inventory::Instance->RemoveAt(Row, Column);
    }
    else
    {
        if(!Item->GetBaseItem()->IsEquipment()) 
        {
            return;
        }
        Inventory::Instance->DequipFromType(Item->GetBaseItem()->Type);
    }

    Slot.Item = nullptr;
}

bool UIBag::StoreAtFirstSlot(UIItem* Item)
{
    int Row, Column;
    if(Inventory::Instance->StoreAtFirstEmpty(Item->GetBaseItem(), Row, Column))
    {
        InventorySlots[Row][Column].Item = Item;
        Item->CurrentSlotNumber = InventorySlots[Row][Column].Id;
        Item->RelativePosition = InventorySlots[Row][Column].Position;
        return true;
    }
    return  false;
}

// std::vector<std::map<Vector2, UIItem*>> InventorySlots;
bool UIBag::Store(UIItem* SelectedItem, Vector2 EventPos)
{
    SelectedItem->FreeFromMouse();
    bool HasPut = false;

    if(Rectangle(AbsolutePosition.x + INVENTORY_START_WIDTH, AbsolutePosition.y + INVENTORY_START_HEIGHT, SLOT_WIDTH*SLOTS_COLUMNS, SLOT_HEIGHT*SLOTS_ROWS).Contains(EventPos))
    {
        Vector2 EventRelativePos = EventPos - AbsolutePosition - Vector2(INVENTORY_START_WIDTH, INVENTORY_START_HEIGHT);
        int NewSlotColumn = (int) (EventRelativePos.x / SLOT_WIDTH);
        int NewSlotRow = (int) (EventRelativePos.y / SLOT_HEIGHT);
        SlotSpace& SlotToPlace = InventorySlots[NewSlotRow][NewSlotColumn];
        
        if(GetSlot(SelectedItem->CurrentSlotNumber).SlotType == ItemClass::General && SlotToPlace.Item != nullptr)
        {
            PlaceAtSlot(GetSlot(SelectedItem->CurrentSlotNumber), SlotToPlace.Item);
        }
        PlaceAtSlot(SlotToPlace, SelectedItem);
        HasPut = true;

    }
    else if(SelectedItem->GetBaseItem()->IsEquipment())
    {
        for(auto Slot : EquipSlot)
        {
            auto SlotPos = AbsolutePosition + Slot.Position;
            if(Rectangle(SlotPos.x, SlotPos.y, SLOT_WIDTH, SLOT_HEIGHT).Contains(EventPos) && Slot.SlotType == SelectedItem->GetBaseItem()->Type)
            {
                if(Slot.Item != nullptr)
                {
                    PlaceAtSlot(GetSlot(SelectedItem->CurrentSlotNumber), Slot.Item);
                }
                PlaceAtSlot(Slot, SelectedItem);
                HasPut = true;
                break;
            }
        }
    }
    
    if( !HasPut)
    {
        SelectedItem->RelativePosition = GetSlot(SelectedItem->CurrentSlotNumber).Position;
    }

    return HasPut;
}

void UIBag::ThrowFromSlot(UIItem* ItemToThrow)
{
    RemoveFromSlot(ItemToThrow);

    GameObject* DroppedItem = new GameObject();
    DroppedItem->AddComponent(ItemToThrow->GetBaseItem().get());
    DroppedItem->Box.SetPosition(Player::Self->Parent.Box.Position());
    Engine::Instance().CurrentScene().AddGameObj(DroppedItem);

    ItemToThrow->Close();
}


SlotSpace& UIBag::GetSlot(int SlotNumber)
{
    int Row = SlotNumber / SLOTS_COLUMNS;
    int Column = SlotNumber % SLOTS_COLUMNS;
    return InventorySlots[Row][Column];
}


//________________________________________________________#UIBagButton________________________________________________________


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




