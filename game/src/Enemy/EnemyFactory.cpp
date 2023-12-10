#include "Enemy/EnemyFactory.hpp"
#include "Enemy/Enemy.hpp"
#include <iostream>

Enemy* EnemyFactory::CreateEnemy(GameObject& Parent, EnemyType Type, Stats EnemyStats){
    switch(Type){
        case SLIME:
        {
            Sprite* SlimeSprite = new Sprite(Parent, "./res/img/enemy/slime_5x6f_67x44px.png", 30, 6, 5, 0.1f);

            return Enemy::Builder(Parent, "Slime", EnemyStats)
                .AddSprite(SlimeSprite)
                .SetCollider(new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, SlimeSprite->GetHeight()/3)))
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 6, 6, 0.2f, true, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 5, 0.15f, true, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 24, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 24, 1, 0.0f, false, true}))
                .SetInitialState(ENEMY_IDLE)
                .Build();
        }  
        break ;
        case GRUB:
        {
            Sprite* GrubSprite = new Sprite(Parent, "res/img/enemy/grub_4x4f_32x32px.png",32,4,4, 0.1f);
            GrubSprite->SetScale(Vector2(2,2));

            return Enemy::Builder(Parent, "Grub", EnemyStats)
                .AddSprite(GrubSprite)
                .SetCollider(new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, GrubSprite->GetHeight()/3)))
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 4, .2, true, true}))
                .AddState(ENEMY_FIGHTING, new EnemyFighting({ENEMY_FIGHTING, 0, 1, 0, false, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 8, 4, .2, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 12, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 12, 1, 0.0f, false, true}))

                .SetInitialState(ENEMY_IDLE)
                .Build();
        } 
        break;
        case MUSHROOM:
        {
            Sprite* MushrommSprite = new Sprite(Parent, "res/img/enemy/mushroom_enemy.png",27,9,3, 0.1f);
            MushrommSprite->SetScale(Vector2(2,2));
            return Enemy::Builder(Parent, "Mushroom", EnemyStats)
                .AddSprite(MushrommSprite)
                .SetCollider(new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, MushrommSprite->GetHeight()/3)))
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 9, .2, true, true}))
                .AddState(ENEMY_FIGHTING, new EnemyFighting({ENEMY_FIGHTING, 0, 1, 0, false, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 8, 4, .2, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 18, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 18, 1, 0.0f, false, true}))
                .SetInitialState(ENEMY_IDLE)
                .Build();
         }  
        break ;
        case WOLF:
        {
            Sprite* WolfSprite = new Sprite(Parent, "res/img/enemy/wolf_7x3f_80x45f.png",21,7,3,0.1f);
            WolfSprite->SetScale(Vector2(2,2));
            return Enemy::Builder(Parent, "Wolf", EnemyStats)
                .AddSprite(WolfSprite)
                .SetCollider(new AARectangle(Parent, ColliderKind::Rigid, Rectangle(0,0,WolfSprite->GetWidth()/2,WolfSprite->GetHeight()/2)))
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 7, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 5, .2, true, true}))
                .AddState(ENEMY_FIGHTING, new EnemyFighting({ENEMY_FIGHTING, 0, 1, 0, false, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 8, 4, .2, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 21, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 21, 1, 0.0f, false, true}))
                .SetInitialState(ENEMY_IDLE)
                .Build();
        }  
        break ;
        default:
        break;
    }
    return nullptr; //to avoid the warning
}

Enemy* EnemyFactory::CreateEnemy(GameObject& Parent, EnemyType Type, Vector2 Position, Stats EnemyStats){
    Enemy* Enemy = CreateEnemy(Parent, Type, EnemyStats);
    Parent.Box.SetCenter(Position);
    return Enemy;
}
