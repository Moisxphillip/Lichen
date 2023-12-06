#include "Enemy/Slime.hpp"

#include "Core/Input.hpp"
#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Tools/AStar.hpp"

#include "Character/Player.hpp"
#include "TestScene.hpp"
#include "Definitions.hpp"
#include "Tools/DistanceTrigger.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define SLIME_IDLE SMState::Type01
#define SLIME_WALK SMState::Type02
#define SLIME_HURT SMState::Type03

int Slime::EnemyCount = 0;

#define ENEMY_DEFAULT_INVULNERABILITY 0.6f

Slime::Slime(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Parent.Represents = ENEMY_MASK | ENEMY_ATK_MASK;
    Parent.Interacts = PLAYER_MASK | ENEMY_MASK | CollisionMask::Terrain;
    MyStats = Stats{100, 100, 1, 0, 5, 5, 5, 5, 0, 0, 0, 0};
    EnemyCount++;
    _HitCooldown.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
    _HitCooldown.Update(ENEMY_DEFAULT_INVULNERABILITY);
    _FlickTime = 0.0f;
    _Flick = false;
}

#include "Mechanics/Equipment.hpp"
Slime::~Slime()
{
    EnemyCount--;
}

#define SLIME_DEFAULT_FRICTION 0.1f
void Slime::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    // Sprite* slime = new Sprite(Parent, "./res/img/slime.png", 12, 6, 2, 0.2f);
    Sprite* slime = new Sprite(Parent, "./res/img/enemy/slime_5x6f_67x44px.png", 30, 6, 5, 0.1f);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(slime->GetWidth(), slime->GetHeight()));
    AddSprite(slime);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,slime->GetHeight()/3));
    MyCollider->SetFriction(SLIME_DEFAULT_FRICTION);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    Parent.AddComponent(new Attack(Parent, MyStats, {10, 1, ScalingStats::Strength}, Parent.Interacts));
    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
    //Create an idle state
    StateInfo SI = {SLIME_IDLE, 6, 6, 0.2f, true, true}; //these are for setting up the spritesheet portion on update
    AddState(SLIME_IDLE, new SlimeIdle(SI));
    SetState(SLIME_IDLE);

    //Walk state
    SI = {SLIME_WALK, 0, 5, 0.15f, true, true};
    AddState(SLIME_WALK, new SlimeWalk(SI));
    
    //Hurt state
    SI = {SLIME_HURT, 24, 1, 0.0f, false, true};
    AddState(SLIME_HURT, new SlimeHurt(SI));
}


void Slime::SMUpdate(float Dt)
{
    if(!_HitCooldown.Finished())
    {
        _HitCooldown.Update(Dt);
        if(_HitCooldown.Get() > _FlickTime)
        {
            _FlickTime+=0.2f;
            if(!_Flick)
            {
                _Sections[0].get()->SetAddColor(Color("#ffffff"));
                _Flick = true;
            }
            else
            {
                _Sections[0].get()->SetAddColor(Color("#000000"));
                _Flick = false;
            }
        }
        
        if (_HitCooldown.Finished())
        {
            _Sections[0].get()->SetAddColor(Color("#000000"));
            _Flick = false;
            _FlickTime = 0.0f;
        }
    }    
}


#include "Definitions.hpp"
void Slime::SMOnCollision(GameObject& Other)
{
    if(_CurrState != SLIME_HURT && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK))
    {
        //  if(_CurrState != PLAYER_HURT && _CurrState != PLAYER_DASH && _CurrState != PLAYER_DEATH 
        // && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & ENEMY_ATK_MASK))
        // {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats);
        if(MyStats.HP <= 0)
        {
            // SetState(PLAYER_DEATH);
            GameObject* Drop = new GameObject();
            Drop->Depth = DepthMode::Dynamic;
            Drop->AddComponent(new Equipment(*Drop));
            Drop->Box.SetCenter(Parent.Box.Center());
            Engine::Instance().CurrentScene().AddGameObj(Drop);
            Parent.RequestDelete();
            return;
        }
        SetState(SLIME_HURT);
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}

#define MOVE_SPD 2000

void Slime::MoveTo(Vector2 Destiny, float Dt)
{
    Destiny.x < Parent.Box.Center().x ? SetFlip(Flip::N) : SetFlip(Flip::H);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);

    if(Distance.MagnitudeSquared() < MOVE_SPD*MOVE_SPD *Dt)
    {
        Parent.Box.SetCenter(Destiny);
    }
    MyCollider->ApplyForce(Distance.Normalized()*MOVE_SPD); 
}


//------------------------------IDLE------------------------------
#define DETECTION_RANGE 380*380
#define MEMORY_RANGE 550*550

SlimeIdle::SlimeIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void SlimeIdle::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : DETECTION_RANGE+1;

    if(DistSq < DETECTION_RANGE)
    {
        Sm.SetState(SLIME_WALK);
        return;
    }
}

//------------------------------WALK------------------------------
#define SEARCH_TIME 0.8f
#define FOLLOW_RANGE 80*80

SlimeWalk::SlimeWalk(const StateInfo& Specs)
: GenericState(Specs)
{
    _SearchPath.SetLimit(SEARCH_TIME + Engine::RandomFloat());
    _SearchPath.Restart();
}


void SlimeWalk::Start()
{
    _UpdateTime = false;
    if(Path.empty())
    {
        return;
    }
    Path = std::queue<Vector2>();
}

void SlimeWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : DETECTION_RANGE+1;

    if(DistSq > MEMORY_RANGE)
    {
        Path = std::queue<Vector2>();
        Sm.SetState(SLIME_IDLE);
        return;
    }

    _UpdateTime = false;
    if(DistSq < FOLLOW_RANGE)
    {
        Path = std::queue<Vector2>();
        reinterpret_cast<Slime*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt);
        return;
    }
    
    _UpdateTime = true;
    if(Player::Self != nullptr && _SearchPath.Finished() && Test01::CollisionMap != nullptr && Path.size()< 4)
    {
        Path = std::queue<Vector2>();//empty old Path values
        _SearchPath.SetLimit(1.0f+ Engine::RandomFloat());
        _SearchPath.Restart();
        // int MinX = (int)Sm.Parent.Box.Center().x/64, MaxX = (int)Player::Self->Parent.Box.Center().x/64;
        // int MinY = (int)Sm.Parent.Box.Center().y/64, MaxY = (int)(Player::Self->Parent.Box.Center().y+32/*offset*/)/64;
        // if(MinX > MaxX)
        // {
        //     std::swap(MinX, MaxX);
        // }
        // if(MinY > MaxY)
        // {
        //     std::swap(MinY, MaxY);
        // }
        // MinX-=3;
        // MinY-=3;
        // MaxX+=3;
        // MaxY+=3;
        
        std::vector<Point> path = AStar::Search(
            /*AStar::TrimSubgrid(*/*Test01::CollisionMap/*, MinY, MinX, MaxY-MinY, MaxX-MinX)*/,
            {(int)Sm.Parent.Box.Center().x/64, 
            (int)Sm.Parent.Box.Center().y/64}, 
            {(int)Player::Self->Parent.Box.Center().x/64,
            (int)(Player::Self->Parent.Box.Center().y+32)/64});

        for(int i = 1; i < (int)path.size(); i++)
        {
            Path.emplace(Vector2(path[i].x*64 + 32, path[i].y*64 + 32));
        }
    };  

    if(Path.empty())
    {
        return;
    }

    Vector2 NextPoint = Path.front();

    if(Sm.Parent.Box.Center().DistanceSquared(NextPoint) <  24*24)
    {
        Path.pop();
        if(Path.empty())
        {
            return;
        }
        NextPoint = Path.front();
    }
    reinterpret_cast<Slime*>(&Sm)->MoveTo(NextPoint, Dt);
}

void SlimeWalk::Update(StateMachine& Sm, float Dt)
{
    if(_UpdateTime)
    {
        _SearchPath.Update(Dt);
    }
}

//------------------------------HURT------------------------------
#define ENEMY_DEFAULT_INVULNERABILITY 0.6f

SlimeHurt::SlimeHurt(const StateInfo& Specs)
: GenericState(Specs)
{
    _HurtTime.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
}


void SlimeHurt::Start()
{
    _HurtTime.Restart();
}

void SlimeHurt::Update(StateMachine& Sm, float Dt)
{
    _HurtTime.Update(Dt);
    if(_HurtTime.Finished())
    {
        Sm.SetState(SLIME_IDLE);
        reinterpret_cast<Slime*>(&Sm)->MyCollider->SetFriction(SLIME_DEFAULT_FRICTION);
    }
   
}
