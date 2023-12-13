#include "Enemy/EnemyFactory.hpp"
#include "Enemy/Enemy.hpp"
#include "Enemy/SlimeEnemy.hpp"
#include "Definitions.hpp"
#include "Core/Enum.hpp"
#include <iostream>

Enemy* EnemyFactory::CreateEnemy(GameObject& Parent, EnemyType Type, Stats EnemyStats){
    switch(Type){
        case SLIME:
        {
            Sprite* SlimeSprite = new Sprite(Parent, "./res/img/enemy/slime_5x6f_67x44px.png", 30, 6, 5, 0.1f);

            return Slime::Builder(Parent, "Slime", EnemyStats)
                .AddSprite(SlimeSprite)
                .SetCollider(new AACircle(Parent, ColliderKind::Rigid, Circle(0,0, SlimeSprite->GetHeight()/3)))
                .SetRepresentationMask(ENEMY_MASK | ENEMY_ATK_MASK)
                .SetInteractionMask((PLAYER_MASK | ENEMY_MASK | CollisionMask::Terrain))
                .SetAttackRange(110*110)
                .SetAttackTimePoint(.3f)
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 6, 6, 0.2f, true, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 5, 0.15f, true, true}))
                .AddState(ENEMY_ATTACK, new SlimeAttack({ENEMY_ATTACK, 12, 4, .1, true, true}))
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
                .SetAttackTimePoint(.6f)
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 4, .2, true, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 4, 4, .2, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 12, 1, 0, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 12, 1, 0, false, true}))

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
                .SetAttackTimePoint(.6f)
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, false, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 9, .1, true, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 9, 8, .1, false, true}))
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
                .SetAttackTimePoint(.6f)
                .SetMovimentationSpeed(3000)
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, true, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 0, 5, .1, true, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 7, 7, .1, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 14, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 14, 1, 0.0f, false, true}))
                .SetInitialState(ENEMY_IDLE)
                .Build();
        }  
        break ;
        case GOLEM:
        {
            Sprite* GolemSprite = new Sprite(Parent, "res/img/enemy/golem_4x6f_50x42px.png",24,4,6,0.1f);
            GolemSprite->SetScale(Vector2(2,2));
            return Enemy::Builder(Parent, "Golem", EnemyStats)
                .AddSprite(GolemSprite)
                .SetCollider(new AARectangle(Parent, ColliderKind::Rigid, Rectangle(0,0,GolemSprite->GetWidth()/2,GolemSprite->GetHeight()/2)))
                .SetAttackTimePoint(.6f)
                .SetMovimentationSpeed(1000)
                .AddState(ENEMY_IDLE, new EnemyIdle({ENEMY_IDLE, 0, 1, 0, true, true}))
                .AddState(ENEMY_WALK, new EnemyWalk({ENEMY_WALK, 4, 4, .1, true, true}))
                .AddState(ENEMY_ATTACK, new EnemyAttack({ENEMY_ATTACK, 8, 8, .1, false, true}))
                .AddState(ENEMY_HURT, new EnemyHurt({ENEMY_HURT, 20, 1, 0.0f, false, true}))
                .AddState(ENEMY_DEATH, new EnemyDeath({ENEMY_DEATH, 20, 1, 0.0f, false, true}))
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
