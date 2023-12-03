#include "Character/Player.hpp"

#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Tools/Tools.hpp"
#include "Components/Sprite.hpp"

#include "Mechanics/Combat.hpp"
#include "Mechanics/Equipment.hpp"
#include "Definitions.hpp"
#include "Npc/Critter.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define PLAYER_IDLE SMState::Type01
#define PLAYER_WALK SMState::Type02
#define PLAYER_DASH SMState::Type03
#define PLAYER_ATTACK SMState::Type04
#define PLAYER_SPECIAL SMState::Type05
#define PLAYER_HURT SMState::Type06
#define PLAYER_DEATH SMState::Type07


//Player specific defines
#define PLAYER_DEFAULT_FRICTION 0.1f
#define PLAYER_DEFAULT_INVULNERABILITY 1.5f

Player* Player::Self;

Player::Player(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    _Type = COMPONENT_PLAYER;
    Parent.Represents = PLAYER_MASK;
    Parent.Interacts = ENEMY_ATK_MASK | INTERACT_MASK | CollisionMask::Terrain;
    _MyStats = Stats{100, 100, 1, 0, 5, 25, 5, 5, 0, 3, 0, 100};
    MyCollider = nullptr;
    Self = this;
    _HitCooldown.SetLimit(PLAYER_DEFAULT_INVULNERABILITY);
    _HitCooldown.Restart();
}

Player::~Player()
{
    Self = nullptr;
}

void Player::SMStart()
{
    Engine::Instance().CurrentScene().Cam.Follow(&Parent);
    //Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/Player/elf_10x8f_60x60px.png", 80, 10, 8);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    AddSprite(Sheet);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,Sheet->GetWidth()/5));
    MyCollider->Offset.y = 32;
    MyCollider->SetFriction(PLAYER_DEFAULT_FRICTION);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {PLAYER_IDLE, 30, 2, 0.15f, true, true}; //these are for setting up the spritesheet portion on update
    AddState(PLAYER_IDLE, new PlayerIdle(SI));
    SetState(PLAYER_IDLE);

    //Create a walk state
    SI = {PLAYER_WALK, 0, 10, 0.08f, true, true};
    AddState(PLAYER_WALK, new PlayerWalk(SI));
    
    //Dash
    SI = {PLAYER_DASH, 32, 3, 0.2f, false, true};
    AddState(PLAYER_DASH, new PlayerDash(SI));
    
    //Attack
    SI = {PLAYER_ATTACK, 10, 4, 0.2f, false, true};
    AddState(PLAYER_ATTACK, new PlayerAttack(SI));
    
    //Special
    SI = {PLAYER_SPECIAL, 20, 6, 0.2f, false, true};
    AddState(PLAYER_SPECIAL, new PlayerSpecial(SI));
    
    //Hurt
    SI = {PLAYER_HURT, 30, 5, 0.06f, false, true};
    AddState(PLAYER_HURT, new PlayerHurt(SI));

    //Death
    SI = {PLAYER_DEATH, 50, 3, 0.2f, false, true};
    AddState(PLAYER_DEATH, new PlayerDeath(SI));
    
}

void Player::SMPhysicsUpdate(float Dt)
{

}

bool Flick = false;
float FlickTime = 0.0f;
void Player::SMUpdate(float Dt)
{   
    Input& Ip = Input::Instance();
    
    if(!_HitCooldown.Finished())
    {
        _HitCooldown.Update(Dt);
        if(_HitCooldown.Get() > FlickTime)
        {
            FlickTime+=0.2f;
            if(!Flick)
            {
                _Sections[0].get()->SetAddColor(Color("#ffffff"));
                Flick = true;
            }
            else
            {
                _Sections[0].get()->SetAddColor(Color("#000000"));
                Flick = false;
            }
        }
        
        if (_HitCooldown.Finished())
        {
            _Sections[0].get()->SetAddColor(Color("#000000"));
            Flick = false;
            FlickTime = 0.0f;
        }
    }

    if(Ip.MouseJustPressed(MouseButton::Middle))
    {
        GameObject* birb = new GameObject();
        birb->AddComponent(new Bird(*birb));
        birb->Box.SetCenter(Ip.MousePosition());
        Engine::Instance().CurrentScene().AddGameObj(birb);
    }
    
}

#define KNOCKBACK 60000
void Player::SMOnCollision(GameObject& Other)
{
    //Damage received
    if(_HitCooldown.Finished() && _CurrState != PLAYER_HURT && _CurrState != PLAYER_DASH && _CurrState != PLAYER_DEATH 
        && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & ENEMY_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, _MyStats);
        if(_MyStats.HP <= 0)
        {
            SetState(PLAYER_DEATH);
            return;
        }
        SetState(PLAYER_HURT);
        _HitCooldown.Restart();
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * KNOCKBACK);
        MyCollider->SetFriction(0.02f);
        return;
    }

    //Equipment Interaction
    else if(Other.Contains(COMPONENT_EQUIP) && Input::Instance().KeyJustPressed(Key::F))
    {
        Equipment* Equip = (Equipment*)Other.GetComponent(COMPONENT_EQUIP);
        std::cout 
            << "Equipment Data:\nVit: " << Equip->Attributes.Vit
            << "\nStr: " << Equip->Attributes.Str
            << "\nDex: " << Equip->Attributes.Dex
            << "\nInt: " << Equip->Attributes.Int << '\n';
        //TODO Register once and ignore after, because an OnCollision can run more than once each loop
    }


}

void Player::AddExperience(int Exp)
{
    _MyStats.Exp +=Exp; 
    //TODO Add level up structure and function around here
}

void Player::DoAttack()
{
    Input& Ip = Input::Instance();
    MyCollider->SetVelocity(Vector2(0.0f, 0.0f));
    GameObject* Atk = new GameObject;
    Atk->Represents = PLAYER_ATK_MASK;
    Vector2 Direction = Parent.Box.Center().DistVector2(Ip.MousePosition()).Normalized();
    Direction.x <= 0 ? SetFlip(Flip::H) : SetFlip(Flip::N);

    Atk->Box.SetCenter(Parent.Box.Center() + Vector2(Direction.x/std::fabs(Direction.x) *40.0f, 0.0f));
    
    Atk->AddComponent(new Attack(*Atk, GetStats(), {10, 1, ScalingStats::Strength}, Parent.Interacts, 0.3));
    AACircle* Ball = new AACircle(*Atk, ColliderKind::Trigger, Circle(0,0, 80));
    Ball->SetFriction(0.0f);
    Atk->AddComponent(Ball);

    Engine::Instance().CurrentScene().AddGameObj(Atk);
    SetState(PLAYER_ATTACK);
}

Stats& Player::GetStats()
{
    return _MyStats;
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
        reinterpret_cast<Player*>(&Sm)->DoAttack();
        return;
    }

    if(Ip.MouseJustPressed(MouseButton::Right))
    {
        Sm.SetState(PLAYER_SPECIAL);
        return;
    }
    
    if(Ip.MouseJustPressed(MouseButton::Middle))
    {
        Sm.SetState(PLAYER_HURT);
        return;
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
#define WALK_FORCE 3000 //Newtons


PlayerWalk::PlayerWalk(const StateInfo& Specs)
: GenericState(Specs)
{
}

void PlayerWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();

    if(Ip.MouseJustPressed(MouseButton::Left))
    {
        reinterpret_cast<Player*>(&Sm)->DoAttack();
        return;
    }


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
        x == -1 ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
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
#define DASH_FORCE 3000
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

void PlayerAttack::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void PlayerAttack::Update(StateMachine& Sm, float Dt)
{
    _AttackTime.Update(Dt);
    if(_AttackTime.Finished())
    {
        Sm.SetState(PLAYER_IDLE);
    }
}

//------------------------------SPECIAL------------------------------
#define SPECIAL_TIME 0.7f

PlayerSpecial::PlayerSpecial(const StateInfo& Specs)
: GenericState(Specs)
{
    _SpecialTime.SetLimit(ATTACK_TIME);
}

void PlayerSpecial::Start()
{
    _SpecialTime.Restart();
}

void PlayerSpecial::OnCollision(StateMachine& Sm, GameObject& Other)
{
}

void PlayerSpecial::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void PlayerSpecial::Update(StateMachine& Sm, float Dt)
{
    _SpecialTime.Update(Dt);
    if(_SpecialTime.Finished())
    {
        Sm.SetState(PLAYER_IDLE);   
    }
}

//------------------------------HURT------------------------------
#define HURT_TIME 0.3f

PlayerHurt::PlayerHurt(const StateInfo& Specs)
: GenericState(Specs)
{
    _HurtTime.SetLimit(HURT_TIME);
}

void PlayerHurt::Start()
{
    _HurtTime.Restart();
}

void PlayerHurt::OnCollision(StateMachine& Sm, GameObject& Other)
{

}

void PlayerHurt::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void PlayerHurt::Update(StateMachine& Sm, float Dt)
{
    _HurtTime.Update(Dt);
    if(_HurtTime.Finished())
    {
        reinterpret_cast<Player*>(&Sm)->MyCollider->SetFriction(PLAYER_DEFAULT_FRICTION);
        Sm.SetState(PLAYER_IDLE);
    }
}

//------------------------------DEATH-----------------------------
#define DEATH_TIME 0.7f

PlayerDeath::PlayerDeath(const StateInfo& Specs)
: GenericState(Specs)
{
    _DeathTime.SetLimit(ATTACK_TIME);
}

void PlayerDeath::Start()
{
    _DeathTime.Restart();
}

void PlayerDeath::Update(StateMachine& Sm, float Dt)
{
    _DeathTime.Update(Dt);
    if(_DeathTime.Finished())
    {
        Engine::Instance().CurrentScene().Cam.Unfollow();
        Sm.Parent.RequestDelete();
    }
}

