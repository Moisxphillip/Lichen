#include "../lib/PenguinBody.hpp"
#include "../lib/PenguinCannon.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Path.hpp"
#include "../../engine/lib/Engine.hpp"
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
    Parent.Angle = 0;
    _LinearSpeed = 0;
    Sprite* Body = new Sprite(GameObj, FIMG_PENGBODY);
    Parent.Box = Rect(0,0, Body->GetWidth(), Body->GetHeight());
    Collider* CollidePenguin = new Collider(GameObj);
	CollidePenguin->Box = Parent.Box;
    Parent.AddComponent(Body);
    Parent.AddComponent(CollidePenguin);

}

PenguinBody::~PenguinBody()
{
    Player = nullptr;
}

Vector2 PenguinBody::CurrPosition()
{
    return Parent.Box.Center();
}

void PenguinBody::OnCollision(GameObject& Other)
{
    Bullet* Shot = (Bullet*) Other.GetComponent(ComponentType::Type01);
    if(Shot != nullptr)
    {
        if (Shot->TargetsPlayer)
        {
            _HP -= Shot->GetDamage();
            Other.RequestDelete();
            if(_HP<=0)
            {
                Engine::Instance().CurrentState().Cam.Unfollow();
            }
        }
    }
}

void PenguinBody::Render()
{

}

void PenguinBody::Start()
{
    GameObject* Cannon = new GameObject(3);
    PenguinCannon* CannonCub = new PenguinCannon(*Cannon, Engine::Instance().CurrentState().GetGameObjPtr(&Parent));
    Cannon->AddComponent(CannonCub);
    Engine::Instance().CurrentState().AddGameObj(Cannon);
}

void PenguinBody::Update(float Dt)
{
    Parent.Angle+= (Input::Instance().KeyPressedDown(Key::D)-Input::Instance().KeyPressedDown(Key::A))
    * Dt * M_PI;
    _LinearSpeed+= (Input::Instance().KeyPressedDown(Key::S)-Input::Instance().KeyPressedDown(Key::W)) 
    * Dt * LICHEN_PENGACCEL;

    if(_LinearSpeed > LICHEN_PENGSPDMAX)
    {
        _LinearSpeed = LICHEN_PENGSPDMAX;
    }
    else if (_LinearSpeed < -LICHEN_PENGSPDMAX)
    {
        _LinearSpeed = -LICHEN_PENGSPDMAX;
    }
    if (Input::Instance().KeyPressedDown(Key::B))
    {
        _LinearSpeed = 0;
    }
    if(Parent.Box.Center().y < 0 || Parent.Box.Center().y > 1280)
    {
        Parent.Angle = -Parent.Angle;
    }
    if(Parent.Box.Center().x < 0 || Parent.Box.Center().x > 1400)
    {
        Parent.Angle = M_PI - Parent.Angle;
    }
    Vector2 Move(_LinearSpeed*Dt, 0);
    Move.Rotate(Parent.Angle);
    Parent.Box-=Move;

    if(_HP<=0 && !Parent.IsDead())
    {
        GameObject* Death = new GameObject(2);
        Sprite* PengDeath = new Sprite(*Death, FIMG_PENGDEATH, 5,5,1, LICHEN_DEATHFRAMETIME, 1);
        PengDeath->Loop = false;
        Death->Box.h = PengDeath->GetHeight();
        Death->Box.w = PengDeath->GetWidth();
        Death->Box.SetCenter(Parent.Box.Center());
        Death->AddComponent(PengDeath);
        Engine::Instance().CurrentState().AddGameObj(Death);

        GameObject* DeathSound = new GameObject();
        DeathSound->Box = Death->Box;
        Sound* Boom = new Sound(*DeathSound, FAUD_BOOM);
        Boom->Pan = true;
        Boom->SelfDestruct = true; 
        Boom->Play(0);
        DeathSound->AddComponent(Boom);
        Engine::Instance().CurrentState().AddGameObj(DeathSound);

        Parent.RequestDelete();
    }
}
