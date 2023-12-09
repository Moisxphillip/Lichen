#ifndef LICHEN_UI_ITEM
#define LICHEN_UI_ITEM

#include "Mechanics/Item.hpp"

#include "UserInterface/UIComponent.hpp"
#include "UserInterface/UIBasicComponents.hpp"
#include "UserInterface/UIBagMenu.hpp"


class UIItem : public UIMovable
{
private:
    std::shared_ptr<Item> _BaseItem;

public:
    bool Hovering;
    bool IsRightClicking;
    int CurrentSlotNumber;

    UIItem(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
    std::vector<std::string> Classes, std::shared_ptr<Item> BaseItem);
    ~UIItem();

    void GroupStart();

    void OnClick(Vector2 EventPos);
    void OnDoubleClick(Vector2 EventPos);
    void OnRightClick(Vector2 EventPos);
    void OnRelease(Vector2 EventPos);
    void OnHover(Vector2 EventPos);

    void Use();

    std::shared_ptr<Item> GetBaseItem();
};

class UIItemDescriptor : public UIComponent
{
private: 
    UIItem* _Item;
public:
    UIItemDescriptor(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position,
    std::vector<std::string> Classes, UIItem* Item);

    Text* _ItemName;
    Text*  _Description;
    std::vector<Text*> _StatsDescription;
    Text*  _UseText;

    void Start();
    void OnUpdate(Vector2 EventPos, float Dt);
    void ComplementaryRender();
};


class UIItenOptions: public UIGroupComponent {
private:
    UIItem* _Item;
public:
    UIItenOptions(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item);
    void GroupStart();
    void OnUpdate(Vector2 EventPos, float Dt);
};

class UIItenOptionUse: public UIComponent 
{
private:
    UIItem* _Item;
public:
    UIItenOptionUse(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item);
    void Start();
    void OnClick(Vector2 EventPos);
    void OnHover(Vector2 EventPos);
    void OnUpdate(Vector2 EventPos, float Dt);
};

class UIItenOptionThrow: public UIComponent {
private:    
    UIItem* _Item;
public:
    UIItenOptionThrow(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes, UIItem* Item);
    void Start();
    void OnClick(Vector2 EventPos);
    void OnHover(Vector2 EventPos);
    void OnUpdate(Vector2 EventPos, float Dt);
    
};


#endif