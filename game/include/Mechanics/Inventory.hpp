#ifndef LICHEN_INVENTORY
#define LICHEN_INVENTORY

#include "Mechanics/Item.hpp"
#include "Components/Component.hpp"

class Inventory: public Component{
public:
    std::vector<Equipment*> Equiped;
    std::vector<std::vector<Item*>> ItemInventory;

    Inventory(GameObject& Parent);

    void Start();

    bool StoreAtFirstEmpty(Item* Item);
    Item* RemoveAt(int Row, int Column);
    void StoreAt(Item* Item, int Row, int Column);
    void EquipAt(Equipment* Equipment, int Idx);
    Equipment* DequipAt(int Idx);
};

#endif