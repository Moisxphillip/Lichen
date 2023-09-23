#include "../lib/Minion.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Path.hpp"
#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Collider.hpp"
#include "../../engine/lib/XRand.hpp"

Minion::Minion(GameObject& GameObj, std::weak_ptr<GameObject> AlienCenter, float Arc)
: Component(GameObj), _AlienCenter(AlienCenter)
{
    
    _Arc = Arc;
    Parent.Angle = M_PI/2+_Arc;
    Sprite* Mini = new Sprite(GameObj,FIMG_MINION);
    XrandF32 Size(rand());
    float CustomSize = Size.gen()/2;//(0 , 0.5)
    Mini->SetScale(1+CustomSize,1+CustomSize);

    Parent.Box.h = Mini->GetHeight();
    Parent.Box.w = Mini->GetWidth();
    Collider* CollideMinion = new Collider(GameObj);
	CollideMinion->Box = Parent.Box;
    Parent.AddComponent(Mini);
    Parent.AddComponent(CollideMinion);
    _Type = ComponentType::Type02;
}

void Minion::Shoot(Vector2 Target)
{
    //Create gameobject for a projectile
    float Angle = Parent.Box.Center().DistAngle(Target);
    GameObject* GoBullet= new GameObject(4);
    Bullet* Projectile = new Bullet(*GoBullet, Angle, 300.0f,
             15, 900.0f, FIMG_BULLET, 3, true, true);
    GoBullet->Box.SetCenter(Parent.Box.Center());
    GoBullet->AddComponent(Projectile);
    Engine::Instance().CurrentScene().AddGameObj(GoBullet);
}

void Minion::Render()
{
}

void Minion::Start()
{
}

void Minion::Update(float Dt)
{
    if(!_AlienCenter.expired())
    {
        std::shared_ptr<GameObject> CurrCenter = _AlienCenter.lock();
        Vector2 DistToCenter(180,0);
        _Arc += (M_PI/4)*Dt;
        Parent.Angle += (M_PI/4)*Dt;

        DistToCenter.Rotate(_Arc);
        Parent.Box.SetCenter(DistToCenter + CurrCenter->Box.Center());
    }
    else
    {
        Parent.RequestDelete();
    }
}
