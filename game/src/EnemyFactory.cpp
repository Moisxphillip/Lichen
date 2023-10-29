#include "EnemyFactory.hpp"
#include "Enemy.hpp"
#include <iostream>

Enemy* EnemyFactory::CreateEnemy(GameObject& Parent, EnemyType Type){
    switch(Type){
        case GRUB:{
            Sprite* GrubSprite = new Sprite(Parent, "./res/img/grub.png",32,8,4);
            GrubSprite->SetScale(Vector2(2,2));

            return Enemy::Builder(Parent, "Grub")
                .AddSprite(GrubSprite)
                .SetCollider(new AARectangle(Parent, ColliderKind::Rigid, Rectangle(0,0,GrubSprite->GetWidth()/2,GrubSprite->GetHeight()/2)))
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 4, .2, true, true}))
                .AddState(ENEMY_PURSUIT, new EnemyPursuit({ENEMY_PURSUIT, 0, 4, .2, true, true}))
                .AddState(ENEMY_FIGHTING, new EnemyFighting({ENEMY_FIGHTING, 0, 1, 0, false, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 8, 4, .2, false, true}))
                .SetInitialState(ENEMY_IDLE)
                .Build();
            }  break ;
        default:
        break;
    }
    return nullptr; //to avoid the warning
}

Enemy* EnemyFactory::CreateEnemy(GameObject& Parent, EnemyType Type, Vector2 Position){
    Enemy* Enemy = CreateEnemy(Parent, Type);
    Parent.Box.SetCenter(Position);
    return Enemy;
}