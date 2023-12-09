#ifndef LICHEN_UI_BAG_MENU
#define LICHEN_UI_BAG_MENU

#define SLOT_WIDTH  50
#define SLOT_HEIGHT  50
#define INVENTORY_START_WIDTH 4
#define INVENTORY_START_HEIGHT 232
#define SLOTS_ROWS 4
#define SLOTS_COLUMNS 5


#include "UserInterface/UIComponent.hpp"
#include "UserInterface/UIItem.hpp"
#include "UserInterface/UIBasicComponents.hpp"
#include "Core/Camera.hpp"

class UIItem;

struct SlotSpace
{
    int Id;
    UIItem* Item;
    Vector2 Position;
    ItemClass SlotType;
};

class UIItem;

class UIBag : public UIGroupComponent {
private:
    std::vector<SlotSpace> EquipSlot;  
    std::vector<std::vector<SlotSpace>> InventorySlots;

public:
    static Vector2 LastBagRelativePosition;

    UIBag(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    ~UIBag();

    void GroupStart();
    void Close();
    void OnLateUpdate(Vector2 EventPos, float Dt);
    void PlaceAtSlot(SlotSpace& SlotToPlace, UIItem* Item);
    void RemoveFromSlot(UIItem* Item);
    
    bool StoreAtFirstSlot(UIItem* Item);
    bool Store(UIItem* Item, Vector2 EventPos);

    void ThrowFromSlot(UIItem* Item);
    SlotSpace& GetSlot(int SlotNumber);
};

class UIBagButton : public UIComponent {
private:
    bool _IsOpened;
   
public:

    UIBagButton(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);

    void Start();
    void OnRelease(Vector2 EventPos);

};


class UIBagClose : public UIComponent {
public:
    UIBagClose(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnClick(Vector2 EventPos);
};


// class UIBagEquipmentSpace: public UIComponent {};


#endif