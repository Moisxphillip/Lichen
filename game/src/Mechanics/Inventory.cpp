#include "Mechanics/Inventory.hpp"

Inventory* Inventory::Instance = nullptr;

Inventory::Inventory(GameObject& Parent):Component(Parent)
{
    Instance = this;

    _Equiped .emplace_back(std::shared_ptr<Equipment>(new Equipment(Parent, ItemClass::Boot)));
    _Equiped .emplace_back(std::shared_ptr<Equipment>(new Equipment(Parent, ItemClass::Bracelet)));
    _Equiped .emplace_back(std::shared_ptr<Equipment>(new Equipment(Parent, ItemClass::Collar)));
    _Equiped .emplace_back(std::shared_ptr<Equipment>(new Equipment(Parent, ItemClass::Legs)));
    
    _ItemInventory = 
        {
            std::vector<std::shared_ptr<Item>>(5, std::shared_ptr<Item>()),
            std::vector<std::shared_ptr<Item>>(5, std::shared_ptr<Item>()),
            std::vector<std::shared_ptr<Item>>(5, std::shared_ptr<Item>()),
            std::vector<std::shared_ptr<Item>>(5, std::shared_ptr<Item>())
        };
}

Inventory::~Inventory()
{
    Instance = nullptr;

    for (auto Row = rbegin(_ItemInventory); Row != rend(_ItemInventory); ++Row) 
    {
        for (auto Item = rbegin(*Row); Item != rend(*Row); ++Item) 
        {
            Item->reset();
        }
    }
    
    this->_ItemInventory.clear();

    for (auto Equipment = rbegin(_Equiped); Equipment != rend(_Equiped); ++Equipment) 
    {
        Equipment->reset();
    }
    
    this->_Equiped.clear();
}

void Inventory::Start()
{   
    StoreAtFirstEmpty(std::shared_ptr<Item>(new Equipment(Parent, "labuluca", "desc", "res/img/UI/botas.png","res/img/UI/botas.png", EquipStats{1,0,2,3}, ItemClass::Boot)));
    StoreAtFirstEmpty(std::shared_ptr<Item>(new Equipment(Parent, "asdas", "desc", "res/img/UI/botas2.png","res/img/UI/botas.png", EquipStats{1,0,2,3}, ItemClass::Boot)));
}

bool Inventory::StoreAtFirstEmpty(std::shared_ptr<Item> BaseItem)
{
    for(int i =0; i < _ItemInventory.size(); i++)
    {
        for(int j =0; j < _ItemInventory[i].size(); j++)
        {
            if(!_ItemInventory[i][j])
            {
                _ItemInventory[i][j] = BaseItem;
                return true;
            }
        }
    }
    return false;
}

bool Inventory::StoreAtFirstEmpty(std::shared_ptr<Item> BaseItem, int& Row, int& Column)
{
    for(int i =0; i < _ItemInventory.size(); i++)
    {
        for(int j =0; j < _ItemInventory[i].size(); j++)
        {
            if(!_ItemInventory[i][j])
            {
                _ItemInventory[i][j] = BaseItem;
                Row = i;
                Column = j;
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Item> Inventory::RemoveAt(int Row, int Column)
{
    std::shared_ptr<Item> RemovedItem = _ItemInventory[Row][Column];
    _ItemInventory[Row][Column].reset();
    return RemovedItem;
}

void Inventory::StoreAt(std::shared_ptr<Item> BaseItem, int Row, int Column)
{
    _ItemInventory[Row][Column] = BaseItem;
}

void Inventory::Equip(std::shared_ptr<Equipment> BaseEquipment)
{
    for(auto& Slot : _Equiped)
    {
        if(Slot->Type == BaseEquipment->Type)
        {
            Slot = std::shared_ptr<Equipment>(BaseEquipment);
            BaseEquipment->UseItem();
            return;
        }
    }
}

std::shared_ptr<Equipment> Inventory::DequipFromType(ItemClass Type)
{
    for(auto& Slot : _Equiped)
    {
        if(Slot->Type == Type)
        {
            std::shared_ptr<Equipment> RemovedEquipment = Slot;
            RemovedEquipment->OnRemove();
            Slot.reset();
            return RemovedEquipment;
        }
    }
    return {};
}

std::vector<std::shared_ptr<Equipment>>& Inventory::GetEquiped()
{
    return _Equiped;
}

std::vector<std::vector<std::shared_ptr<Item>>>& Inventory::GetItemInventory()
{
    return _ItemInventory;
}