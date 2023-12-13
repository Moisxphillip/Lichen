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

#define PLAYER_REC_STAMINA_TIME 10.0f
#define PLAYER_REC_MANA_TIME 1.5f

#define PLAYER_SPECIAL_COST 20

Player* Player::Self = nullptr;

Player::Player(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    _Type = COMPONENT_PLAYER;
    Parent.Represents = PLAYER_MASK;
    Parent.Interacts = ENEMY_ATK_MASK | INTERACT_MASK | CollisionMask::Terrain;
    _MyStats = Stats{100, 100, 1, 0, 5, 5, 5, 5, 2, 3, 50, 100};
    _ExpToLevelUp = Combat::LevelUpExp(_MyStats.Level);
    MyCollider = nullptr;
    Self = this;
    _HitCooldown.SetLimit(PLAYER_DEFAULT_INVULNERABILITY);
    _HitCooldown.Update(PLAYER_DEFAULT_INVULNERABILITY);
    
    _ManaRec.SetLimit(PLAYER_REC_MANA_TIME);
    _StaminaRec.SetLimit(PLAYER_REC_STAMINA_TIME);
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
    if(_MyStats.Mana != _MyStats.MaxMana)
    {
        _ManaRec.Update(Dt);
        if(_ManaRec.Get() >= PLAYER_REC_MANA_TIME - (PLAYER_REC_MANA_TIME * float(_MyStats.Int)/100.0f))
        {
            _MyStats.Mana++;
            _ManaRec.Restart();
        }
    }
    
    if(_MyStats.Stamina != _MyStats.MaxStamina)
    {
        _StaminaRec.Update(Dt);
        if(_StaminaRec.Get() >= PLAYER_REC_STAMINA_TIME - (PLAYER_REC_STAMINA_TIME * float(_MyStats.Dex)/100.0f))
        {
            _MyStats.Stamina++;
            _StaminaRec.Restart();
        }
    }

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
}

#define KNOCKBACK 60000
void Player::SMOnCollision(GameObject& Other)
{
    //Damage received
    if(_HitCooldown.Finished() && _CurrState != PLAYER_HURT && _CurrState != PLAYER_DASH && _CurrState != PLAYER_DEATH 
        && Other.Contains(COMPONENT_ATTACK) && static_cast<bool>(Other.Represents & ENEMY_ATK_MASK))
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, _MyStats, Parent.Box.Center());
        if(_MyStats.HP <= 0)
        {
            SetState(PLAYER_DEATH);
            return;
        }
        SoundHurt();
        SetState(PLAYER_HURT);
        _HitCooldown.Restart();
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * KNOCKBACK);
        MyCollider->SetFriction(0.02f);
        return;
    }

    //Equipment Interaction
    else if(Other.Contains(COMPONENT_EQUIP) && Input::Instance().KeyJustPressed(Key::F))
    {
        // Equipment* Equip = (Equipment*)Other.GetComponent(COMPONENT_EQUIP);
        // std::cout 
        //     << "Equipment Data:\nVit: " << Equip->Attributes.Vit
        //     << "\nStr: " << Equip->Attributes.Str
        //     << "\nDex: " << Equip->Attributes.Dex
        //     << "\nInt: " << Equip->Attributes.Int << '\n';
        // //TODO Register once and ignore after, because an OnCollision can run more than once each loop
    }


}

#include "Components/Text.hpp"
#include "Components/CameraFollower.hpp"
#include "Tools/TimedText.hpp"
void Player::LevelUpMsg()
{
    Color NumColor("#ffffff");
    std::string Prompt =  "Nivel "+ std::to_string(_MyStats.Level)+ " alcancado!";
    GameObject* Lvl = new GameObject();
    Lvl->Depth = DepthMode::Foreground;
    Text* Txt = new Text(*Lvl,"./res/ttf/alagard.ttf", 40, TextStyle::BLENDED, Prompt, NumColor);
    Lvl->AddComponent(Txt);
    Lvl->AddComponent(new TimedText(*Lvl, Txt, NumColor, 0.2f, 1.5f, 0.2f));
    CameraFollower* Cf = new CameraFollower(*Lvl);
    Cf->Offset = Vector2(640 - Txt->GetDimensions().x*0.5f, 200);
    Lvl->AddComponent(Cf);
    Engine::Instance().CurrentScene().AddGameObj(Lvl);
}

void Player::AddExperience(int Exp)
{
    if(_MyStats.Level == 20)
    {
        return;
    }
    _MyStats.Exp +=Exp;
    if(_MyStats.Exp >=  _ExpToLevelUp)
    {
        _MyStats.Level++;
        int Leftovers = _MyStats.Exp - _ExpToLevelUp;
        _MyStats.Exp = 0;
        _ExpToLevelUp = Combat::LevelUpExp(_MyStats.Level);
        AddExperience(Leftovers);
        //TODO Signal stats system about the points to allocate
        LevelUpMsg();
    }
}

void Player::DoAttack()
{
    Input& Ip = Input::Instance();
    MyCollider->SetVelocity(Vector2::ZERO);
    GameObject* Atk = new GameObject;
    Atk->Represents = PLAYER_ATK_MASK;
    Vector2 Direction = Parent.Box.Center().DistVector2(Ip.MousePosition()).Normalized();
    Direction.x <= 0 ? SetFlip(Flip::H) : SetFlip(Flip::N);

    Atk->Box.SetCenter(Parent.Box.Center() + Vector2(Direction.x/std::fabs(Direction.x) *40.0f, 0.0f));
    _MyStats.Str;
    Atk->AddComponent(new Attack(*Atk, GetStats(), {_MyStats.Str * 2, 1, ScalingStats::Strength}, Parent.Interacts, 0.3));
    AACircle* Ball = new AACircle(*Atk, ColliderKind::Trigger, Circle(0,0, 80));
    Ball->SetFriction(0.0f);
    Atk->AddComponent(Ball);

    SoundAtk();

    Engine::Instance().CurrentScene().AddGameObj(Atk);
    SetState(PLAYER_ATTACK);
}
#include "Tools/ElementLoader.hpp"
void Player::SoundAtk()
{
    int i = Engine::RandomUint()%5;
    switch(i)
    {
        case 0:
            FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/player_atk_1.ogg", 20);
            break;
        case 1:
            FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/player_atk_2.ogg", 20);
            break;
        case 2:
            FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/player_atk_3.ogg", 20);
            break;
        case 3:
            FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/player_atk_4.ogg", 20);
            break;
        case 4:
            FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/player_atk_5.ogg", 20);
            break;
        default:
            break;
    }

    i = Engine::RandomUint()%2;
    if(i)
    {
        FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/attack_slash_1.ogg", 30);
        return;
    }
    FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/player/attack_slash_2.ogg", 30);
}

void Player::SoundHurt()
{
    int i = Engine::RandomUint()%5;
    switch(i)
    {
        case 0:
            FastCreate::PlayOnce("./res/audio/player/player_hurt_1.ogg", 20);
            break;
        case 1:
            FastCreate::PlayOnce("./res/audio/player/player_hurt_2.ogg", 20);
            break;
        case 2:
            FastCreate::PlayOnce("./res/audio/player/player_hurt_3.ogg", 20);
            break;
        case 3:
            FastCreate::PlayOnce("./res/audio/player/player_hurt_4.ogg", 20);
            break;
        case 4:
            FastCreate::PlayOnce("./res/audio/player/player_hurt_5.ogg", 20);
            break;
        default:
            break;
    }
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
        reinterpret_cast<Player*>(&Sm)->DoAttack();//TODO move hitbox creation to a timer inside attack state once the sprites are done
        return;
    }

    if(Ip.MouseJustPressed(MouseButton::Right) && Player::Self->GetStats().Mana > PLAYER_SPECIAL_COST)
    {
        Player::Self->GetStats().Mana-=PLAYER_SPECIAL_COST;
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

    if(Ip.KeyJustPressed(Key::Space) && Player::Self->GetStats().Stamina > 0)
    {
        Player::Self->GetStats().Stamina--;
        Sm.SetState(PLAYER_DASH);
    }
}

//------------------------------WALK------------------------------
#define WALK_FORCE 3500 //Newtons


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

    if(Ip.MouseJustPressed(MouseButton::Right) && Player::Self->GetStats().Mana > PLAYER_SPECIAL_COST)
    {
        Player::Self->GetStats().Mana-=PLAYER_SPECIAL_COST;
        Sm.SetState(PLAYER_SPECIAL);
        return;
    }

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);
    
    if(x == 0 && y ==0) //condition for changing to idle state
    {
        Sm.SetState(PLAYER_IDLE);
        reinterpret_cast<Player*>(&Sm)->MyCollider->SetVelocity(Vector2::ZERO);
        return;
    }
    
    Sm.LastDirection = Vector2(x,y).Normalized();
    //Change direction
    if(x!=0)
    {
        x == -1 ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
    }

    //Go to dash
    if(Ip.KeyJustPressed(Key::Space) && Player::Self->GetStats().Stamina > 0)
    {
        Player::Self->GetStats().Stamina--;
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
#define ATTACK_TIME 0.5f

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
        reinterpret_cast<Player*>(&Sm)->MyCollider->SetVelocity(Vector2::ZERO);
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
        reinterpret_cast<Player*>(&Sm)->MyCollider->SetVelocity(Vector2::ZERO);  
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
        reinterpret_cast<Player*>(&Sm)->MyCollider->SetVelocity(Vector2::ZERO);
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

