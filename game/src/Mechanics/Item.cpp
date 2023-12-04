

#include "Mechanics/Item.hpp"


Item::Item(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile): 
    Component(Parent), Name(Name), Description(Description), UISpriteFile(UISpriteFile), ItemSpriteFile(ItemSpriteFile){}

void Item::Start()
{
    UISprite = new Sprite(Parent, UISpriteFile);
}

void Item::Update(float Dt)
{
    // TODO fluctuate position, maybe add shadow
    // TODO interface, player close, pick
}

void Item::Render()
{
    if(ItemSprite)
    {
        ItemSprite->Render();
    }
}

void Item::SetUseText(std::string UseText)
{
    this->UseText = UseText;
}

void Item::UseItem(){}


// __________________________________________________________________ #Equipment __________________________________________________________________

Equipment::Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile):Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile){}

Equipment::Equipment(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, EquipStats Stats):
    Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile), _Stats(Stats){}

void Equipment::UseItem()
{
    // TODO add stats
}

void Equipment::OnRemove()
{
    // TODO remove Stats
}

void Equipment::SetStats(EquipStats Stats)
{
    _Stats = Stats;
}

EquipStats Equipment::GetStats()
{
    return  _Stats;
}

// __________________________________________________________________ #Consumable __________________________________________________________________


Consumable::Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile):Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile){}


Consumable::Consumable(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int InstantHealingPoints):
    Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile), _InstantHealingPoints(InstantHealingPoints){}

void Consumable::UseItem()
{
    // TODO restore life
}

void Consumable::SetInstantHealingPoints(int InstantHealingPoints)
{
    _InstantHealingPoints = InstantHealingPoints;
}

int Consumable::GetInstantHealingPointss()
{
    return _InstantHealingPoints;
}
    
// __________________________________________________________________ #Food __________________________________________________________________

//     int _HealingPoints

Food::Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile):Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile){}

Food::Food(GameObject& Parent, std::string Name, std::string Description, std::string UISpriteFile, std::string ItemSpriteFile, int _HealingPoints):
    Item(Parent, Name, Description, UISpriteFile, ItemSpriteFile), _HealingPoints(_HealingPoints){}

void Food::UseItem()
{
    // TODO set slow heal
}

void Food::SetHealingPoints(int HealingPoints)
{
    _HealingPoints = HealingPoints;
}

int Food::GetHealingPoints()
{
    return  _HealingPoints;
}