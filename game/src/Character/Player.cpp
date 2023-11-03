#include "Character/Player.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"
#include "Combat.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define PLAYER_IDLE SMState::Type01
#define PLAYER_WALK SMState::Type02
#define PLAYER_DASH SMState::Type03
#define PLAYER_ATTACK SMState::Type04


//Player specific defines
#define PLAYER_DEFAULT_FRICTION 0.1f

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
    MyCollider->SetFriction(PLAYER_DEFAULT_FRICTION);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {PLAYER_IDLE, 0, 5, 0.3, true, true}; //these are for setting up the spritesheet portion on update
    PlayerIdle* player = new PlayerIdle(SI);
    AddState(PLAYER_IDLE, player);
    SetState(PLAYER_IDLE);

    //Create a walk state
    SI = {PLAYER_WALK, 5, 5, 0.3, true, true};
    PlayerWalk* walk = new PlayerWalk(SI);
    AddState(PLAYER_WALK, walk);
    
    //Dash
    SI = {PLAYER_DASH, 10, 5, 0.3, true, true};
    PlayerDash* dash = new PlayerDash(SI);
    AddState(PLAYER_DASH, dash);
    
    //Attack
    SI = {PLAYER_ATTACK, 15, 5, 0.3, true, true};
    PlayerAttack* atk = new PlayerAttack(SI);
    AddState(PLAYER_ATTACK, atk);
    
}

void Player::SMPhysicsUpdate(float Dt)
{

}

void Player::SMUpdate(float Dt)
{
    
}

// #include <iostream>
// Stats Def{50, 50, 1, 0, 15, 0, 0, 0};
void Player::SMOnCollision(GameObject& Other)
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

    if(Ip.MouseJustPressed(MouseButton::Left))
    {
        Sm.SetState(PLAYER_ATTACK);
    }

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);

    if(x!=0 ||y !=0)//condition for changing to walk state
    {
        Sm.SetState(PLAYER_WALK);
        return;
    }

    if(Ip.KeyJustPressed(Key::Space))
    {
        Sm.SetState(PLAYER_DASH);
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
    
    Sm.LastDirection = Vector2(x,y).Normalized();
    //Change direction
    if(x!=0)
    {
        x == -1 ? Sm.SetFlip(Flip::N) : Sm.SetFlip(Flip::H);
    }

    //Go to dash
    if(Ip.KeyJustPressed(Key::Space))
    {
        // Sm.LastDirection = Vector2(x, y).Normalized();
        Sm.SetState(PLAYER_DASH);
    }


    //Walk mechanic
    Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information

    Plr->MyCollider->ApplyForce(Sm.LastDirection*WALK_FORCE);
}

//------------------------------DASH------------------------------
#define DASH_FORCE 2000
#define DASH_TIME 0.5f
#define DASH_FRICTION 0.01f

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

#include "Tools/Tools.hpp"
void PlayerDash::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    if(_DashForce == 0)
    {
        return;
    }

    Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information
    Plr->MyCollider->SetFriction(DASH_FRICTION);
    Plr->MyCollider->ApplyForce(Sm.LastDirection*_DashForce*Attenuation(_DashTime.Get()/DASH_TIME, 0.05f, 0.5f));
}

void PlayerDash::Update(StateMachine& Sm, float Dt)
{
    _DashTime.Update(Dt);
    if(_DashTime.Finished())
    {
        Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information
        Plr->MyCollider->SetFriction(PLAYER_DEFAULT_FRICTION);
        Sm.SetState(PLAYER_IDLE);
    }
}

//------------------------------ATTACK------------------------------
#define ATTACK_TIME 0.7f

PlayerAttack::PlayerAttack(const StateInfo& Specs)
: GenericState(Specs)
{
    _AttackTime.SetLimit(ATTACK_TIME);
}

void PlayerAttack::Start()
{
    _AttackTime.Restart();
}

void PlayerAttack::OnCollision(StateMachine& Sm, GameObject& Other)
{
    // if(_DashForce != 0 && (Other.Represents & CollisionMask::Terrain) != CollisionMask::None)
    // {
    // }
}

#include "Tools/Tools.hpp"
void PlayerAttack::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    // Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information
    // // Plr->MyCollider->SetFriction(DASH_FRICTION);
    // // Plr->MyCollider->ApplyForce(Sm.LastDirection*_DashForce*Attenuation(_DashTime.Get()/DASH_TIME));
}

void PlayerAttack::Update(StateMachine& Sm, float Dt)
{
    _AttackTime.Update(Dt);
    if(_AttackTime.Finished())
    {
        Sm.SetState(PLAYER_IDLE);
        // Player* Plr = reinterpret_cast<Player*>(&Sm); //Cast to access child class information
        // Plr->MyCollider->SetFriction(PLAYER_DEFAULT_FRICTION);
    }
}

