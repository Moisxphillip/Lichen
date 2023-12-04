// #include "Mechanics/Inventory.hpp"

// Inventory::Inventory(GameObject& Parent):Component(Parent)
// {
//     std::vector<Equipment*> Equiped = std::vector<Equipment*>(5, nullptr);
//     std::vector<std::vector<Item*>> ItemInventory = 
//     {
//          std::vector<Item*>(5, nullptr),
//          std::vector<Item*>(5, nullptr),
//          std::vector<Item*>(5, nullptr),
//          std::vector<Item*>(5, nullptr)
//     };
// }

// bool Inventory::StoreAtFirstEmpty(Item* Item)
// {
//     for(int i =0; i < ItemInventory.size(); i++)
//     {
//         for(int j =0; j < ItemInventory[i].size(); j++)
//         {
//             if(!ItemInventory[i][j])
//             {
//                 ItemInventory[i][j] = Item;
//                 return true;
//                 // TODO reload of simply put in uI
//             }
//         }
//     }
//     return false;
// }

// Item* Inventory::RemoveAt(int Row, int Column)
// {
//     Item* RemovedItem = ItemInventory[Row][Column];
//     RemovedItem = nullptr;
//     return RemovedItem;
// }

// void Inventory::StoreAt(Item* Item, int Row, int Column)
// {
//     ItemInventory[Row][Column] = Item;
// }

// void Inventory::EquipAt(Equipment* Equipment, int Idx)
// {
//     Equiped[Idx] = Equipment;
// }

// Equipment* Inventory::DequipAt(int Idx)
// {
//     Equipment* RemovedEquipment = Equiped[Idx];
//     RemovedEquipment = nullptr;
//     return RemovedEquipment;
// }