#include "Character/Player.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"
#include "Combat.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define PLAYER_IDLE SMState::Type01
#define PLAYER_WALK SMState::Type02
#define PLAYER_DASH SMState::Type03


//Player specific defines


Player* Player::Self;

Player::Player(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Self = this;
}

Player::~Player()
{
    Self = nullptr;
}

void Player::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/frame.png", 20, 5, 4);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    AddSprite(Sheet);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,Sheet->GetWidth()/5));
    MyCollider->Offset.y = 32;
    MyCollider->SetFriction(0.1f);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {PLAYER_IDLE, 0, 5, 0.5, true, true}; //these are for setting up the spritesheet portion on update
    PlayerIdle* player = new PlayerIdle(SI);
    AddState(PLAYER_IDLE, player);
    SetState(PLAYER_IDLE);

    //Create a walk state
    SI = {PLAYER_WALK, 5, 5, 0.5, true, true};
    PlayerWalk* walk = new PlayerWalk(SI);
    AddState(PLAYER_WALK, walk);
    
    SI = {PLAYER_DASH, 10, 5, 0.5, true, true};
    PlayerDash* dash = new PlayerDash(SI);
    AddState(PLAYER_DASH, dash);
    
}

void Player::SMPhysicsUpdate(float Dt)
{

}

void Player::SMUpdate(float Dt)
{
    
}


// #include <iostream>
// Stats Def{50, 50, 1, 0, 15, 0, 0, 0};
void Player::OnCollision(GameObject& Other)
{
    //Leftovers from combat tests. Far from ideal implementation, but gives an idea on how it should work
    // Stats Atk{50, 50, 1, 0, 0, 25, 25, 0};
    // AttackData Dta{5, (ScalingStats)(ScalingStats::Strength | ScalingStats::Dexterity)};
    // std::cout << Def << '\n';
    // int x =  Combat::Calculate(Atk, Dta, Def);
    // std::cout <<"This round damage: " << x << "\n\n";
}

//------------------------------IDLE------------------------------
PlayerIdle::PlayerIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void PlayerIdle::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);

    if(x!=0 ||y !=0)//condition for changing to walk state
    {
        Sm.SetState(PLAYER_WALK);
        return;
    }
}

//------------------------------WALK------------------------------
#define WALK_FORCE 2000 //Newtons


PlayerWalk::PlayerWalk(const StateInfo& Specs)
: GenericState(Specs)
{
}

void PlayerWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);
    
    if(x == 0 && y ==0) //condition for changing to idle state
    {
        Sm.SetState(PLAYER_IDLE);
        return;
    }
    
    //Change direction
    if(x!=0)
    {
        x == -1 ? Sm.SetFlip(Flip::N) : Sm.SetFlip(Flip::H);
    }

    //Go to dash
    if(Ip.KeyJustPressed(Key::Space))
    {
        Sm.LastDirection = Vector2(x, y).Normalized();
        Sm.SetState(PLAYER_DASH);
    }


    //Walk mechanic
    Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information

    Plr->MyCollider->ApplyForce(Vector2(x,y).Normalized()*WALK_FORCE);
}

//------------------------------DASH------------------------------
#define DASH_FORCE 6000
#define DASH_TIME 0.7f

PlayerDash::PlayerDash(const StateInfo& Specs)
: GenericState(Specs)
{
    _DashTime.SetLimit(DASH_TIME);
}

void PlayerDash::Start()
{
    _DashForce = DASH_FORCE;
    _DashTime.Restart();
}

void PlayerDash::OnCollision(StateMachine& Sm, GameObject& Other)
{
    if(_DashForce != 0 && (Other.Represents & CollisionMask::Terrain) != CollisionMask::None)
    {
        _DashForce = 0;
    }
}

void PlayerDash::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    if(_DashForce == 0)
    {
        return;
    }

    Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information
    Plr->MyCollider->ApplyForce(Sm.LastDirection*_DashForce);
}

void PlayerDash::Update(StateMachine& Sm, float Dt)
{
    _DashTime.Update(Dt);
    if(_DashTime.Finished())
    {
        Sm.SetState(PLAYER_IDLE);
    }
}

