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
    float Angle = Parent.Box.Center().DistAngle(Input::Instance().MousePosition());
    Vector2 ExtraDistance(50,0);
    ExtraDistance.Rotate(Angle);
    GameObject* GoBullet= new GameObject(5);
    Bullet* Projectile = new Bullet(*GoBullet, Angle, LICHEN_BULLETSPD,
             LICHEN_BULLETDMG, LICHEN_BULLETDIST, FIMG_PENGBULLET, 4, false, false);
    GoBullet->Box.SetCenter(Parent.Box.Center());
    GoBullet->Box+=ExtraDistance;
    GoBullet->AddComponent(Projectile);
    Engine::Instance().CurrentState().AddGameObj(GoBullet);
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
        Parent.Angle = Parent.Box.Center().DistAngle(Input::Instance().MousePosition());
        if(Input::Instance().MousePressedDown(MouseButton::Left) && _Cooldown.Get() > 0.3)
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
