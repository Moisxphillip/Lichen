#ifndef LICHEN_ITEM
#define LICHEN_ITEM

#include "Components/Component.hpp"
#include "Components/Sprite.hpp"

struct EquipStats
{
    int Vit = 0,
        Str = 0,
        Dex = 0,
        Int = 0;

    bool Active = false;
};

enum class ItemClass
{
    General,
    Boot,
    Collar,
    Bracelet,
    Legs
};


class Item : public Component
{
protected:
    Item(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, ItemClass Type);
    Item(GameObject& Parent, ItemClass Type);

public:
    std::string UISpriteFile;
    std::string ItemSpriteFile;
    std::string Name;
    std::string Description;
    std::string UseText;
    ItemClass Type;

    Sprite* UISprite;
    Sprite* ItemSprite;

    Item(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
    
    ~Item();

    void Start();
    void Update(float Dt);
    void Render();
    void SetUseText(std::string UseText);
    virtual bool IsEquipment();

    void Throw();

    virtual void UseItem();
};

class Equipment : public Item
{
private:
    EquipStats _Stats;
    
public:
    Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
    Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, EquipStats Stats, ItemClass Type);
    Equipment(GameObject& Parent, ItemClass Type);

    void UseItem();
    void OnRemove();
    bool IsEquipment();

    void SetStats(EquipStats Stats);
    EquipStats GetStats();
};

class Consumable : public Item
{
private:
    int _InstantHealingPoints;

public:
    Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
    Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int InstantHealingPoints);

    void UseItem();

    void SetInstantHealingPoints(int InstantHealingPoints);
    int GetInstantHealingPointss();
    
};

class Food : public Item
{
private:
    int _HealingPoints;

public:
    Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile);
    Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int _HealingPoints);

    void UseItem();

    void SetHealingPoints(int HealingPoints);
    int GetHealingPoints();
};

#endif
