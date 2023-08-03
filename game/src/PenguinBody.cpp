#include "../lib/PenguinBody.hpp"
#include "../lib/PenguinCannon.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Path.hpp"
#include "../../engine/lib/Game.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Sound.hpp"
#include "../../engine/lib/Collider.hpp"

PenguinBody* PenguinBody::Player;

PenguinBody::PenguinBody(GameObject& GameObj)
: Component(GameObj)
{
    Player = this;
    _Speed = Vector2(0,0);
    _HP = 100;
    GameObjAssoc.Angle = 0;
    _LinearSpeed = 0;
    Sprite* Body = new Sprite(GameObj, FIMG_PENGBODY);
    GameObjAssoc.Box = Rect(0,0, Body->GetWidth(), Body->GetHeight());
    Collider* CollidePenguin = new Collider(GameObj);
	CollidePenguin->Box = GameObjAssoc.Box;
    GameObjAssoc.AddComponent(Body);
    GameObjAssoc.AddComponent(CollidePenguin);

}

PenguinBody::~PenguinBody()
{
    Player = nullptr;
}

Vector2 PenguinBody::CurrPosition()
{
    return GameObjAssoc.Box.Center();
}

void PenguinBody::Collided(GameObject& Other)
{
    Bullet* Shot = (Bullet*) Other.GetComponent("Bullet");
    if(Shot != nullptr)
    {
        if (Shot->TargetsPlayer)
        {
            _HP -= Shot->GetDamage();
            Other.RequestDelete();
            if(_HP<=0)
            {
                Game::Instance().GetState().Cam.Unfollow();
            }
        }
    }
}

bool PenguinBody::Is(std::string Type)
{
    return ("PenguinBody" == Type);
}

void PenguinBody::Render()
{

}

void PenguinBody::Start()
{
    GameObject* Cannon = new GameObject();
    PenguinCannon* CannonCub = new PenguinCannon(*Cannon, Game::Instance().GetState().GetGameObjPtr(&GameObjAssoc));
    Cannon->AddComponent(CannonCub);
    Game::Instance().GetState().AddGameObj(Cannon);
}

void PenguinBody::Update(float Dt)
{
    GameObjAssoc.Angle+= (Input::Instance().IsKeyDown(K_D)-Input::Instance().IsKeyDown(K_A))
    * Dt * M_PI;
    _LinearSpeed+= (Input::Instance().IsKeyDown(K_S)-Input::Instance().IsKeyDown(K_W)) 
    * Dt * LICHEN_PENGACCEL;

    if(_LinearSpeed > LICHEN_PENGSPDMAX)
    {
        _LinearSpeed = LICHEN_PENGSPDMAX;
    }
    else if (_LinearSpeed < -LICHEN_PENGSPDMAX)
    {
        _LinearSpeed = -LICHEN_PENGSPDMAX;
    }

    // if(GameObjAssoc.Box.Center().y < 0 || GameObjAssoc.Box.Center().y > 1280)
    // {
    //     GameObjAssoc.Angle = -GameObjAssoc.Angle;
    // }
    // if(GameObjAssoc.Box.Center().x < 0 || GameObjAssoc.Box.Center().x > 1400)
    // {
    //     GameObjAssoc.Angle = M_PI - GameObjAssoc.Angle;
    // }
    Vector2 Move(_LinearSpeed*Dt, 0);
    Move.Rotate(GameObjAssoc.Angle);
    GameObjAssoc.Box-=Move;

    if(_HP<=0)
    {
        GameObject* Death = new GameObject();
        Sprite* PengDeath = new Sprite(*Death, FIMG_PENGDEATH, 5, LICHEN_DEATHFRAMETIME, 1);
        PengDeath->Loop = false;
        Death->Box.h = PengDeath->GetHeight();
        Death->Box.w = PengDeath->GetWidth();
        Death->Box.SetCenter(GameObjAssoc.Box.Center());
        Death->AddComponent(PengDeath);
        Game::Instance().GetState().AddGameObj(Death);

        GameObject* DeathSound = new GameObject();
        DeathSound->Box = Death->Box;
        Sound* Boom = new Sound(*DeathSound, FAUD_BOOM);
        Boom->Pan = true;
        Boom->SelfDestruct = true; 
        Boom->Play(0);
        DeathSound->AddComponent(Boom);
        Game::Instance().GetState().AddGameObj(DeathSound);

        GameObjAssoc.RequestDelete();
    }
}
