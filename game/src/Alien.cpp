#include "../lib/Alien.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Minion.hpp"
#include "../lib/PenguinBody.hpp"
#include "../lib/Path.hpp"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Sound.hpp"
#include "../../engine/lib/Collider.hpp"

int Alien::AlienCount = 0;

Alien::Alien(GameObject& GameObj, int NumMinions)
: Component(GameObj)
{
    _HP = 100;
    _NumMinions = NumMinions;
    _Speed = Vector2(LICHEN_ALIENSPD,LICHEN_ALIENSPD);
    Sprite *SpriteAlien = new Sprite(GameObj, FIMG_ALIEN);
    Parent.Box.h = SpriteAlien->GetHeight();
    Parent.Box.w = SpriteAlien->GetWidth();
    Collider* CollideAlien = new Collider(GameObj);
	CollideAlien->Box = Parent.Box;
    Parent.AddComponent(SpriteAlien);
    Parent.AddComponent(CollideAlien);
    _CurrState = AlienState::REST;
    _Rest.Restart();
    AlienCount++;
    _WaitTime.seed(rand());
    _ExtraTime = _WaitTime.gen();
}

Alien::~Alien()
{
    AlienCount--;
}

void Alien::Collided(GameObject& Other)
{
    Bullet* Shot = (Bullet*) Other.GetComponent("Bullet");
    if(Shot != nullptr)
    {
        if (!Shot->TargetsPlayer)
        {
            _HP -= Shot->GetDamage();
            Other.RequestDelete();
        }
    }
}

void Alien::Start()
{
    _MinionVec.reserve(_NumMinions);
    for(int i = 0; i< _NumMinions; i++)
    {
        GameObject* MinionObj = new GameObject;
        Minion* NewMinion = new Minion(*MinionObj, Engine::Instance().GetState().GetGameObjPtr(&Parent),(2.0f* M_PI * i)/_NumMinions);
        MinionObj->AddComponent(NewMinion);
        _MinionVec.push_back(Engine::Instance().GetState().AddGameObj(MinionObj));
    }
}

void Alien::Update(float Dt)
{
    //Alien Rotation
    Parent.Angle -= (ROTFRAC/2)*Dt;

    if(_CurrState == AlienState::MOVING && PenguinBody::Player!=nullptr)
    {
        Vector2 Distance = Parent.Box.Center() - Destination;
    
        Vector2 Direction = Distance.Normalized();
        Direction *= _Speed * Dt;
        Parent.Box -= Direction;
        if(Direction.Magnitude() >= Distance.Magnitude())
        {
            Parent.Box += Distance;
            _CurrState = AlienState::REST;
            _Rest.Restart();

            float Closest = 1e7; //A big number for quick substitution
            int Index = 0;
            for(int i = 0; i < _NumMinions; i++)
            {
                //Gets the center of a minion, then the distance between it and the penguin
                float Dist = _MinionVec[i].lock()->Box.Center().Distance(PenguinBody::Player->CurrPosition());
                if(Dist < Closest)
                {
                    Closest = Dist;
                    Index = i;
                }
            }
            Minion* ChosenToShoot = (Minion*) _MinionVec[Index].lock()->GetComponent("Minion");
            ChosenToShoot->Shoot(PenguinBody::Player->CurrPosition());
            _ExtraTime = _WaitTime.gen();
        }        
    }
    else if (_CurrState == AlienState::REST)
    {
        _Rest.Update(Dt);
        if(_Rest.Get() >= 1+_ExtraTime)
        {
            if(PenguinBody::Player!=nullptr)
            {
                Destination = PenguinBody::Player->CurrPosition();
            }
            _CurrState = AlienState::MOVING;
        }        
    }

    if(_HP <= 0)
    {
        for(int i = 0; i < _NumMinions; i++)
        {
            GameObject* Death = new GameObject();
            Sprite* AlienDeath = new Sprite(*Death, FIMG_MINIONDEATH, 4, LICHEN_DEATHFRAMETIME, 1);
            AlienDeath->Loop = false;
            Death->Box.h = AlienDeath->GetHeight();
            Death->Box.w = AlienDeath->GetWidth();
            Death->Box.SetCenter(_MinionVec[i].lock()->Box.Center());
            Death->AddComponent(AlienDeath);
            Engine::Instance().GetState().AddGameObj(Death);
            _MinionVec[i].lock()->RequestDelete(); //Request delete for minions
        }

        GameObject* Death = new GameObject();
        Sprite* AlienDeath = new Sprite(*Death, FIMG_ALIENDEATH, 4, LICHEN_DEATHFRAMETIME, 1);
        
        AlienDeath->Loop = false;
        Death->Box.h = AlienDeath->GetHeight();
        Death->Box.w = AlienDeath->GetWidth();
        Death->Box.SetCenter(Parent.Box.Center());
        Death->AddComponent(AlienDeath);
        Engine::Instance().GetState().AddGameObj(Death);
        //Audio track is longer than animation, so plays as an external Engine object
        GameObject* DeathSound = new GameObject();
        DeathSound->Box = Death->Box;
        Sound* Boom = new Sound(*DeathSound, FAUD_BOOM);
        Boom->Pan = true;
        Boom->SelfDestruct = true; 
        Boom->Play(0);
        DeathSound->AddComponent(Boom);
        Engine::Instance().GetState().AddGameObj(DeathSound);

        Parent.RequestDelete(); //Request delete for alien
    }
}

void Alien::Render()
{
}

bool Alien::Is(std::string Type)
{
    return (Type == "Alien");
}
