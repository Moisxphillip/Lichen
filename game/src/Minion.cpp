#include "../lib/Minion.hpp"
#include "../lib/Bullet.hpp"
#include "../lib/Path.hpp"
#include "../../engine/lib/Game.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Collider.hpp"
#include "../../engine/lib/XRand.hpp"

Minion::Minion(GameObject& GameObj, std::weak_ptr<GameObject> AlienCenter, float Arc)
: Component(GameObj), _AlienCenter(AlienCenter)
{
    
    _Arc = Arc;
    GameObjAssoc.Angle = M_PI/2+_Arc;
    Sprite* Mini = new Sprite(GameObj,FIMG_MINION);
    XrandF32 Size(rand());
    float CustomSize = Size.gen()/2;//(0 , 0.5)
    Mini->SetScale(1+CustomSize,1+CustomSize);

    GameObjAssoc.Box.h = Mini->GetHeight();
    GameObjAssoc.Box.w = Mini->GetWidth();
    Collider* CollideMinion = new Collider(GameObj);
	CollideMinion->Box = GameObjAssoc.Box;
    GameObjAssoc.AddComponent(Mini);
    GameObjAssoc.AddComponent(CollideMinion);
}

void Minion::Shoot(Vector2 Target)
{
    //Create gameobject for a projectile
    float Angle = GameObjAssoc.Box.Center().DistAngle(Target);
    GameObject* GoBullet= new GameObject;
    Bullet* Projectile = new Bullet(*GoBullet, Angle, LICHEN_BULLETSPD,
             LICHEN_BULLETDMG, LICHEN_BULLETDIST, FIMG_BULLET, 3, true, true);
    GoBullet->Box.SetCenter(GameObjAssoc.Box.Center());
    GoBullet->AddComponent(Projectile);
    Game::Instance().GetState().AddGameObj(GoBullet);
}

bool Minion::Is(std::string Type)
{
    return (Type == "Minion");
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
        _Arc += ROTFRAC*Dt;
        GameObjAssoc.Angle += ROTFRAC*Dt;

        DistToCenter.Rotate(_Arc);
        GameObjAssoc.Box.SetCenter(DistToCenter + CurrCenter->Box.Center());
    }
    else
    {
        GameObjAssoc.RequestDelete();
    }
}
