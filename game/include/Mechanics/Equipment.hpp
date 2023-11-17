#ifndef GAME_EQUIPS
#define GAME_EQUIPS

#include "Components/Component.hpp"


struct EquipStats
{
    int Vit = 0,
        Str = 0,
        Dex = 0,
        Int = 0;

    bool Active = false;
};

class Equipment : public Component
{
    private:

    public:
        EquipStats Attributes;
        Equipment(GameObject& Parent);
        void OnCollision(GameObject& Other);

};


#endif//GAME_EQUIPS
