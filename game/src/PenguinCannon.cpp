#include "../lib/PenguinCannon.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Path.hpp"
#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Collider.hpp"

PenguinCannon::PenguinCannon(GameObject& GameObj, std::weak_ptr<GameObject> Body)
: Component(GameObj)
{   
    Parent.Angle = 0;
    Sprite* Cannon = new Sprite(GameObj, FIMG_PENGGUN);
    Cannon->SetScale(0.8,0.8);
    Parent.Box = Rect(0,0,Cannon->GetWidth(),Cannon->GetHeight());
    _Body = Body;
    Parent.Box.SetCenter(_Body.lock()->Box.Center());
    Collider* CollideCannon = new Collider(GameObj);
	CollideCannon->Box = Parent.Box;
    Parent.AddComponent(Cannon);
    Parent.AddComponent(CollideCannon);
    _Cooldown.Restart();
}

void PenguinCannon::Shoot()
{
    float Angle = Parent.Box.Center().DistAngle(Input::Instance().GetMouseVector2());
    Vector2 ExtraDistance(50,0);
    ExtraDistance.Rotate(Angle);
    GameObject* GoBullet= new GameObject;
    Bullet* Projectile = new Bullet(*GoBullet, Angle, LICHEN_BULLETSPD,
             LICHEN_BULLETDMG, LICHEN_BULLETDIST, FIMG_PENGBULLET, 4, false, false);
    GoBullet->Box.SetCenter(Parent.Box.Center());
    GoBullet->Box+=ExtraDistance;
    GoBullet->AddComponent(Projectile);
    Engine::Instance().GetState().AddGameObj(GoBullet);
}

bool PenguinCannon::Is(std::string Type)
{
    return ("PenguinCannon" == Type);
}

void PenguinCannon::Render()
{

}

void PenguinCannon::Start()
{

}

void PenguinCannon::Update(float Dt)
{
    _Cooldown.Update(Dt);
    if(!_Body.expired())
    {
        Parent.Box.SetCenter(_Body.lock()->Box.Center());
        Parent.Angle = Parent.Box.Center().DistAngle(Input::Instance().GetMouseVector2());
        if(Input::Instance().MousePress(M_LEFT) && _Cooldown.Get() > 1.8)
        {
            Shoot();
            _Cooldown.Restart();
        }
    }
    else
    {
        Parent.RequestDelete();
    }
}
