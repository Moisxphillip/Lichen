#ifndef LICHEN_ENEMY_FACTORY
#define LICHEN_ENEMY_FACTORY

#include "Enemy.hpp"

enum EnemyType {GRUB,SLIME,GOLEM};

class EnemyFactory{
public:
    static Enemy* CreateEnemy(GameObject& Parent, EnemyType Type);
    static Enemy* CreateEnemy(GameObject& Parent, EnemyType Type, Vector2 Position);
};

#endif