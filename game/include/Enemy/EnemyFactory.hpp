#ifndef LICHEN_ENEMY_FACTORY
#define LICHEN_ENEMY_FACTORY


#include "Enemy.hpp"

enum EnemyType {GRUB, SLIME,MUSHROOM, WOLF, GOLEM};

class EnemyFactory{
public:
    static Enemy* CreateEnemy(GameObject& Parent, EnemyType Type, Stats EnemyStats = DEFAULT_STATS);
    static Enemy* CreateEnemy(GameObject& Parent, EnemyType Type, Vector2 Position, Stats EnemyStats = DEFAULT_STATS);
};

#endif