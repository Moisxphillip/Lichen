#include "Enemy/Slime.hpp"

#include "Core/Input.hpp"
#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Tools/AStar.hpp"

#include "Character/Player.hpp"
#include "TestScene.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define SLIME_IDLE SMState::Type01
#define SLIME_WALK SMState::Type02

Slime::Slime(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
}

void Slime::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* slime = new Sprite(Parent, "./res/img/slime.png", 12, 6, 2, 0.2f);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(slime->GetWidth(), slime->GetHeight()));
    AddSprite(slime);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,slime->GetWidth()/2));
    MyCollider->SetFriction(0.1f);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {SLIME_IDLE, 0, 6, 0.2f, true, true}; //these are for setting up the spritesheet portion on update
    SlimeIdle* Slime = new SlimeIdle(SI);
    AddState(SLIME_IDLE, Slime);
    SetState(SLIME_IDLE);

    //Create a walk state
    SI = {SLIME_WALK, 6, 6, 0.2f, true, true};
    SlimeWalk* Dum = new SlimeWalk(SI);
    AddState(SLIME_WALK, Dum);
}


#define MOVE_SPD 100

void Slime::MoveTo(Vector2 Destiny, float Dt)
{
    Destiny.x > Parent.Box.x ? SetFlip(Flip::N) : SetFlip(Flip::H);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);

    if(Distance.MagnitudeSquared() < MOVE_SPD*MOVE_SPD *Dt)
    {
        Parent.Box.SetCenter(Destiny);
    }
    MyCollider->SetVelocity(Distance.Normalized()*MOVE_SPD*Dt); 
}


//------------------------------IDLE------------------------------
#define DETECTION_RANGE 300*300

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
    // Input& Ip = Input::Instance();
    // if(Ip.MouseJustPressed(MouseButton::Right))
    // {
    //     Slime* Dum = reinterpret_cast<Slime*>(&Sm);
    //     Dum->Target = Ip.MousePosition();
    //     Sm.SetState(SLIME_WALK);
    //     Dum->Target.x - Dum->Parent.Box.Center().x < 0 ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
    // }
}

//------------------------------WALK------------------------------
SlimeWalk::SlimeWalk(const StateInfo& Specs)
: GenericState(Specs)
{
}

#define FOLLOW_RANGE 80*80

void SlimeWalk::Start()
{
    if(Path.empty())
    {
        return;
    }
    Path = std::queue<Vector2>();
}

void SlimeWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    float DistSq = Player::Self != nullptr ? Player::Self->Parent.Box.Center().DistanceSquared(Sm.Parent.Box.Center()) : DETECTION_RANGE+1;

    if(DistSq >= DETECTION_RANGE)
    {
        Path = std::queue<Vector2>();
        Sm.SetState(SLIME_IDLE);
        return;
    }

    if(DistSq < FOLLOW_RANGE)
    {
        reinterpret_cast<Slime*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center(), Dt);
        return;
    }
    
    if(Player::Self != nullptr && Engine::Instance().GetPing() && Test01::CollisionMap != nullptr)
    {
        Path = std::queue<Vector2>();//to empty old Path values

        std::vector<Point> path = AStar::Search(*Test01::CollisionMap,
            {(int)Sm.Parent.Box.Center().x/64, 
            (int)Sm.Parent.Box.Center().y/64}, 
            {(int)Player::Self->Parent.Box.Center().x/64,
            (int)Player::Self->Parent.Box.Center().y/64});

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

    if(Sm.Parent.Box.Center().DistanceSquared(NextPoint) <  32*32)
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
