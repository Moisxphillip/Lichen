// #ifndef LICHEN_ITEM
// #define LICHEN_ITEM

// #include "Components/Component.hpp"
// #include "Components/Sprite.hpp"

// struct EquipStats
// {
//     int Vit = 0,
//         Str = 0,
//         Dex = 0,
//         Int = 0;

//     bool Active = false;
// };


// class Item : public Component
// {
// public:
//     std::string Name;
//     std::string Description;
//     std::string UseText;

//     Sprite* UISprite;
//     Sprite* ItemSprite;

//     Item(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);

//     void Start();
//     void Update(float Dt);
//     void Render();
//     void SetUseText(std::string UseText);

//     virtual void UseItem();
// };

// class Equipment : public Item
// {
// private:
//     EquipStats _Stats;

// public:
//     Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
//     Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, EquipStats Stats);

//     void UseItem();

//     void SetStats(EquipStats Stats);
//     EquipStats GetStats();
// };

// class Consumable : public Item
// {
// private:
//     int _InstantHealingPoints;

// public:
//     Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
//     Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int _InstantHealingPoints);

//     void UseItem();

//     void SetInstantHealingPoints(int InstantHealingPoints);
//     int GetInstantHealingPointss();
    
// };

// class Food : public Item
// {
// private:
//     int _HealingPoints;

// public:
//     Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
//     Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int _HealingPoints);

//     void UseItem();

//     void SetHealingPoints(int HealingPoints);
//     int GetHealingPoints();
// };

// #endif
