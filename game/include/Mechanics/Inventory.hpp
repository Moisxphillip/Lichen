#ifndef LICHEN_INVENTORY
#define LICHEN_INVENTORY

#include "Mechanics/Item.hpp"
#include "Components/Component.hpp"



class Inventory: public Component{
private:
    std::vector<std::shared_ptr<Equipment>> _Equiped;
    std::vector<std::vector<std::shared_ptr<Item>>> _ItemInventory;

public:
    static Inventory* Instance;

    Inventory(GameObject& Parent);
    ~Inventory();

    void Start();
    
    std::shared_ptr<Item> RemoveAt(int Row, int Column);
    bool StoreAtFirstEmpty(std::shared_ptr<Item> Item);
    bool StoreAtFirstEmpty(std::shared_ptr<Item> Item, int& Row, int& Column);
    void StoreAt(std::shared_ptr<Item>, int Row, int Column);
    void Equip(std::shared_ptr<Equipment> Equipment);
    std::shared_ptr<Equipment> DequipFromType(ItemClass Type);

    std::vector<std::shared_ptr<Equipment>>& GetEquiped();
    std::vector<std::vector<std::shared_ptr<Item>>>& GetItemInventory();
};

#endif