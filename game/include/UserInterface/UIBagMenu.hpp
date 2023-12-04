#ifndef LICHEN_UI_BAG_MENU
#define LICHEN_UI_BAG_MENU

#define SLOT_WIDTH  50
#define SLOT_HEIGHT  50



#include "UserInterface/UIComponent.hpp"
#include "Core/Camera.hpp"
#include "UserInterface/UIBasicComponents.hpp"
#include "UserInterface/UIItem.hpp"

class UIBagButton : public UIComponent {
private:
    bool _IsOpened;
   
public:

    UIBagButton(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);

    void Start();
    void OnRelease(Vector2 EventPos);

};

class UIBag : public UIGroupComponent {
private:
    // std::vector<std::map<Vector2, UIItem*>> InventorySlots;

public:
    static Vector2 LastBagRelativePosition;

    UIBag(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);

    void GroupStart();
    void Close();
    void OnRightClick(Vector2 EventPos);
    void OnLateUpdate(Vector2 EventPos, float Dt);

    bool StoreAtSlot(UIItem* Item, Vector2 EventPos);
};

class UIBagClose : public UIComponent {
public:
    UIBagClose(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnClick(Vector2 EventPos);
};

class UIItenOptions: public UIGroupComponent {
public:
    UIItenOptions(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    void GroupStart();
    void OnUpdate(Vector2 EventPos, float Dt);
};

class UIItenOptionUse: public UIComponent 
{
public:
    UIItenOptionUse(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnHover(Vector2 EventPos);
    void OnUpdate(Vector2 EventPos, float Dt);
};

class UIItenOptionThrow: public UIComponent {
public:
    UIItenOptionThrow(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnHover(Vector2 EventPos);
    void OnUpdate(Vector2 EventPos, float Dt);
    
};


// class UIBagItens : public UIGroupComponent {};

// class UIBagItemSpace: public UIComponent {};

// class UIBagEquipmentSpace: public UIComponent {};


#endif