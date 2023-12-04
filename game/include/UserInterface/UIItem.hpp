#ifndef LICHEN_UI_ITEM
#define LICHEN_UI_ITEM

#include "UserInterface/UIComponent.hpp"
#include "UserInterface/UIBasicComponents.hpp"
#include "Mechanics/Item.hpp"

class UIItem : public UIComponent
{
private:
    Item* BaseItem;

public:
    UIItem(Item* BaseItem);

    void OnDoubleClick(Vector2 EventPos);
    void OnHold(Vector2 EventPos);
    void OnRelease(Vector2 EventPos);

};

class UIItemDescriptor : public UIComponent
{
private:

    Text* _ItemName;
    Text*  _Description;
    std::vector<Text*> _StatsDescription;

public:
    void Start();
    void Update(Vector2 EventPos, float Dt);
};

#endif