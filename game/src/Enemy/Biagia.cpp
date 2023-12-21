#include "Enemy/Biagia.hpp"
#include "Mechanics/Progress.hpp"
#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Character/Player.hpp"
#include "Components/AARectangle.hpp"
#include "Definitions.hpp"
#include "Mechanics/Equipment.hpp"
#include "Core/Input.hpp"


//Define names for the SMState enums, so it's easier to know which state you're using
#define BIAGIA_IDLE SMState::Type01
#define BIAGIA_SPAWN SMState::Type02
#define BIAGIA_ATTACKHORIZ SMState::Type03
#define BIAGIA_POSE SMState::Type04
#define BIAGIA_TELEPORTING SMState::Type05
#define BIAGIA_TELEPORTED SMState::Type06
#define BIAGIA_HURT SMState::Type07
#define BIAGIA_VULNERABLE SMState::Type08


#define ENEMY_DEFAULT_INVULNERABILITY 0.4f
#define MAX_SUMMONS 3
#include "Enemy/EnemyFactory.hpp"


Biagia* Biagia::Self = nullptr;
#include "Tools/MusicPlayer.hpp"
Biagia::Biagia(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Parent.Represents = ENEMY_MASK;
    Parent.Interacts = REFLECTED_BULLET_MASK | PLAYER_ATK_MASK;
    MyStats = Stats{100, 100, 10, 0, 15, 15, 15, 15, 0, 0, 0, 0};
    _HitCooldown.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
    _HitCooldown.Update(ENEMY_DEFAULT_INVULNERABILITY);
    _FlickTime = 0.0f;
    _Flick = false;
    Self = this;
    Shield = nullptr;
    Summons = 0;
    for(int i = 0; i<5; i++)
    {
        Arena[i] = nullptr;
    }
    Progress::DisableSpawn = true;
    Progress::KillMinions = true;
    if(MusicPlayer::Self)
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/boss.ogg");
    }
}

Biagia::~Biagia()
{
    Self = nullptr;
    if(Input::Instance().QuitRequested())
    {
        return;
    }

    if(Player::Self != nullptr)
    {
        Engine::Instance().CurrentScene().Cam.Follow(&(Player::Self->Parent));
    }
    
    //Cleanup Arena
    for(int i = 0; i<5; i++)
    {
        if(Arena[i] != nullptr)
            Arena[i]->RequestDelete();
    }

    if(Shield != nullptr)
    {
        Shield->Parent.RequestDelete();
    }

    Progress::DisableSpawn = false;
    Progress::KillMinions = false;
    if(MusicPlayer::Self)
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/village.ogg");
    }
}

// #define BIAGIA_DEFAULT_FRICTION 0.1f
void Biagia::SMStart()
{
    Sprite* malachi = new Sprite(Parent, "./res/img/boss/biagia_6x6f.png", 36, 6, 6, 0.1f);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(malachi->GetWidth(), malachi->GetHeight()));
    AddSprite(malachi);
    MyCollider = new AACircle(Parent, ColliderKind::Trigger, Circle(0,0,malachi->GetHeight()/4));
    // MyCollider->SetFriction(BIAGIA_DEFAULT_FRICTION);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {BIAGIA_IDLE, 0, 6, 0.1f, true, true}; //these are for setting up the spritesheet portion on update
    AddState(BIAGIA_IDLE, new BiagiaIdle(SI));
    SetState(BIAGIA_IDLE);

    //AtkDown state
    SI = {BIAGIA_SPAWN, 12, 5, 0.1f, false, true};
    AddState(BIAGIA_SPAWN, new BiagiaSpawn(SI));
    
    //Pose state
    SI = {BIAGIA_POSE, 6, 3, 0.1f, false, true};
    AddState(BIAGIA_POSE, new BiagiaTeleportPose(SI));
    
    //TPing state
    SI = {BIAGIA_TELEPORTING, 24, 3, 0.1f, false, true};
    AddState(BIAGIA_TELEPORTING, new BiagiaTeleporting(SI));
    
    //TPd state
    SI = {BIAGIA_TELEPORTED, 30, 3, 0.1f, false, true};
    AddState(BIAGIA_TELEPORTED, new BiagiaTeleported(SI));
    
    //Hurt state
    SI = {BIAGIA_HURT, 18, 1, 0.0f, false, true};
    AddState(BIAGIA_HURT, new BiagiaHurt(SI));
    
    //Vulnerable state
    SI = {BIAGIA_VULNERABLE, 18, 1, 0.0f, true, true};
    AddState(BIAGIA_VULNERABLE, new BiagiaVulnerable(SI));

    SetupArena();
    GameObject* Sh = new GameObject();
    Sh->Depth = DepthMode::Dynamic;
    Shield = new Sprite(*Sh, "./res/img/boss/bubble.png", 4, 4, 1);
    Sh->Box.Redimension(Vector2(Shield->GetWidth(), Shield->GetHeight()));
    Sh->AddComponent(Shield);
    Engine::Instance().CurrentScene().AddGameObj(Sh);
}

void Biagia::SMUpdate(float Dt)
{
    if(Shield != nullptr && Shield->Active)
    {
        Shield->Parent.Box.SetCenter(Parent.Box.Center());
    }

    if(_CurrState != BIAGIA_VULNERABLE && Summons >= MAX_SUMMONS && Enemy::EnemyCount == 0)
    {
        Shield->Active = false;
        SetState(BIAGIA_VULNERABLE);
        Summons = 0;

        GameObject* Sh = new GameObject();
        Sh->Depth = DepthMode::Dynamic;
        Sprite* Shieldn = new Sprite(*Sh, "./res/img/boss/bubble.png", 4, 4, 1, 0.1, 0.4);
        Sh->Box.Redimension(Vector2(Shieldn->GetWidth(), Shieldn->GetHeight()));
        Sh->Box.SetCenter(Parent.Box.Center());
        Sh->AddComponent(Shieldn);
        Engine::Instance().CurrentScene().AddGameObj(Sh);
    }

    if(!_HitCooldown.Finished())
    {
        _HitCooldown.Update(Dt);
        if(_HitCooldown.Get() > _FlickTime)
        {
            _FlickTime+=0.1f;
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

#include "Enemy/Enemy.hpp"
#include "Tools/ElementLoader.hpp"
void Biagia::SMOnCollision(GameObject& Other)
{   
    if (_CurrState == BIAGIA_VULNERABLE && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) 
        && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK) && _HitCooldown.Finished())
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats, Parent.Box.Center());
        int i = Engine::RandomUint()%2;
        switch(i)
        {
            case 0:
                FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage2_hurt1.wav", 20);
                break;
            case 1:
                FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage2_hurt2.wav", 20);
                break;
            default:
                break;
        }
        if(MyStats.HP <= 0)
        {
            // SetState(_DEATH);
            // GameObject* Drop = new GameObject();
            // Drop->Depth = DepthMode::Dynamic;
            // Drop->AddComponent(new Equipment(*Drop));
            // Drop->Box.SetCenter(Parent.Box.Center());
            // Engine::Instance().CurrentScene().AddGameObj(Drop);
            if(Player::Self != nullptr)
            {
                Player::Self->AddExperience(Combat::DeathExp(MyStats.Level)*2);
            }
            Parent.RequestDelete();
            return;
        }
        // SetState(BIAGIA_HURT);
        // MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        // MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}

void Biagia::SetupArena()
{
    for(int i = 0; i<5; i++)
    {
        Arena[i] = new GameObject();
        Arena[i]->Represents = CollisionMask::Terrain;
        Arena[i]->Depth = DepthMode::Foreground;
    }

    Vector2 Center = Parent.Box.Center();
    //Colliders
    Arena[0]->Box.SetPosition(Center - Vector2(0, 360+32));
    Arena[0]->AddComponent(new AARectangle(*Arena[0], ColliderKind::Stationary, Rectangle(0,0,1280, 64)));

    Arena[1]->Box.SetPosition(Center + Vector2(0, 360+32));
    Arena[1]->AddComponent(new AARectangle(*Arena[1], ColliderKind::Stationary, Rectangle(0,0,1280, 64)));

    Arena[2]->Box.SetPosition(Center - Vector2(640+32, 0));
    Arena[2]->AddComponent(new AARectangle(*Arena[2], ColliderKind::Stationary, Rectangle(0,0,64, 720)));

    Arena[3]->Box.SetPosition(Center + Vector2(640+32, 0));
    Arena[3]->AddComponent(new AARectangle(*Arena[3], ColliderKind::Stationary, Rectangle(0,0,64, 720)));

    // New Focal center
    Arena[4]->Box.SetPosition(Parent.Box.Center());
    Engine::Instance().CurrentScene().Cam.Follow(Arena[4]);

    for(int i = 0; i<5; i++)
    {
        Engine::Instance().CurrentScene().AddGameObj(Arena[i]);
    }
}

void Biagia::Spawn()
{

    int i = Engine::RandomUint()%3;
    int Lvl = 6;

    GameObject* Go = new GameObject();
    Stats EnStats = {Stats{50+Lvl, 50+Lvl, Lvl, 0, 5+Lvl, 5+Lvl, 5+Lvl, 5+Lvl, 0, 0, 0, 0}};
    Vector2 Position(300 * Engine::RandomFloat(), 0.0f);
    Position.Rotate(M_PI*2*Engine::RandomFloat());
    Position+=Arena[4]->Box.Position();
    switch(i)
    {
        case 0:
            Go->AddComponent(EnemyFactory::CreateEnemy(*Go, EnemyType::SLIME, Position, EnStats));
            break;
        case 1:
            Go->AddComponent(EnemyFactory::CreateEnemy(*Go, EnemyType::GRUB, Position, EnStats));
            break;
        case 2:
            Go->AddComponent(EnemyFactory::CreateEnemy(*Go, EnemyType::WOLF, Position, EnStats));
            break;
        default:
            break;
    }
    Engine::Instance().CurrentScene().AddGameObj(Go);
    Summons++;

    //TODO poof smoke when spawn
    // _ToSpawn.Restart();

    // int Max = 3+ Engine::RandomUint()%3;
    // for(int i = 0; i<Max; i++)
    // {
    // GameObject* Blt = new GameObject();
    // Blt->Depth = DepthMode::Dynamic;
    // Blt->Represents = ENEMY_ATK_MASK;
    // Sprite* Sprt = new Sprite(*Blt, "./res/img/boss/spark.png", 7, 7, 1, 0.1f);
    // Blt->Box.Redimension(Vector2(Sprt->GetWidth(), Sprt->GetHeight()));
    // Blt->AddComponent(Sprt);
    // Vector2 Dir = Player::Self != nullptr ?  Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center()).Normalized() : Vector2(1, 0);
    // Dir.Rotate((Engine::RandomFloat() - 0.5f)*1.5f);
    // Vector2 Offset = Dir * 100;
    // Blt->Box.SetPosition(Parent.Box.Center() + Offset);
    // Blt->AddComponent(new Projectile(*Blt, Dir*2.0f, Sprt->GetWidth()/3, PLAYER_ATK_MASK | PLAYER_MASK));
    // Blt->AddComponent(new Attack(*Blt, MyStats, {MyStats.Int*2, 1, ScalingStats::Intelect},
    //     Blt->Interacts, 20.0f));
    // Engine::Instance().CurrentScene().AddGameObj(Blt);
    // }
}
//------------------------------IDLE------------------------------


#define IDLE_TIME 1.0f

BiagiaIdle::BiagiaIdle(const StateInfo& Specs)
: GenericState(Specs)
{
    _TeleportChance = 50;
    _ShootChance = 50;
    _ChangeState.SetLimit(IDLE_TIME + 0.5*Engine::RandomFloat());
}

void BiagiaIdle::Start()
{
    _ChangeState.SetLimit(IDLE_TIME + 0.5*Engine::RandomFloat());
    _ChangeState.Restart();
}

void BiagiaIdle::Update(StateMachine& Sm, float Dt)
{
    _ChangeState.Update(Dt);
    if(!_ChangeState.Finished())
    {
        return;
    }

    // float Dist = Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center());

    float Tp = _TeleportChance/100.0f;
    float Shot = _ShootChance/100.0f;
    float Rnd = Engine::RandomFloat();
    
    if(Rnd < Tp || reinterpret_cast<Biagia*>(&Sm)->Summons >= MAX_SUMMONS)
    {
        if( reinterpret_cast<Biagia*>(&Sm)->Summons < MAX_SUMMONS)
        {
            _ShootChance+=10;
            _TeleportChance-=10;
        }

        Sm.SetState(BIAGIA_POSE);
    }
    else
    {
        _ShootChance-=10;
        _TeleportChance+=10;
        Vector2 Dist = Sm.Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());
        Dist.x > 0.0f ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
        if(Progress::KillMinions)
        {
            Progress::KillMinions = false;
        }
        Sm.SetState(BIAGIA_SPAWN);
    }

    // if(Engine::RandomUint() & 1)
    // {
    //     Vector2 Dist = Sm.Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());
    //     Dist.x > 0.0f ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
    //     Dist.y > std::abs(Dist.x) ? Sm.SetState(BIAGIA_SPAWN) : Sm.SetState(BIAGIA_ATTACKHORIZ);
    //     return;
    // }
}

//------------------------------SPAWN------------------------------
BiagiaSpawn::BiagiaSpawn (const StateInfo& Specs)
: GenericState(Specs)
{
    _AtkTime.SetLimit(0.5f);
}

void BiagiaSpawn::Start()
{
    _AtkTime.Restart();
    FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage2_snap.wav", 20);
}

void BiagiaSpawn::Update(StateMachine& Sm, float Dt)
{
    _AtkTime.Update(Dt);
    if(_AtkTime.Finished())
    {
        
        reinterpret_cast<Biagia*>(&Sm)->Spawn();
        Sm.SetState(BIAGIA_IDLE);
    }
}

//------------------------------TELEPORTPOSE------------------------------
#define TELEPORT_TIME 0.3f

BiagiaTeleportPose::BiagiaTeleportPose (const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void BiagiaTeleportPose::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Biagia*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 

void BiagiaTeleportPose::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Sm.SetState(BIAGIA_TELEPORTING);
    }
}


//------------------------------TELEPORTING------------------------------
BiagiaTeleporting::BiagiaTeleporting(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void BiagiaTeleporting::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Biagia*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void BiagiaTeleporting::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Biagia* Mm = reinterpret_cast<Biagia*>(&Sm);
        Mm->MyCollider->Position = Mm->Arena[4]->Box.Position() 
            + Vector2(1000 * (Engine::RandomFloat()-0.5f), 500 * (Engine::RandomFloat()-0.5f));        
        Sm.SetState(BIAGIA_TELEPORTED);
    }
}



//------------------------------ ------------------------------
BiagiaTeleported::BiagiaTeleported(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME+0.1f);
}

void BiagiaTeleported::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Biagia*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void BiagiaTeleported::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Sm.SetState(BIAGIA_IDLE);
    }
}


//------------------------------HURT------------------------------
BiagiaHurt::BiagiaHurt(const StateInfo& Specs)
: GenericState(Specs)
{
}


void BiagiaHurt::Start()
{
}

// reinterpret_cast<Biagia*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void BiagiaHurt::Update(StateMachine& Sm, float Dt)
{
}

void BiagiaHurt::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void BiagiaHurt::OnCollision(StateMachine& Sm, GameObject& Other)
{
}

//------------------------------VULNERABLE------------------------------
#define VULNERABLE_LIMIT 4.0f

BiagiaVulnerable::BiagiaVulnerable (const StateInfo& Specs)
: GenericState(Specs)
{
    _VulnerableTime.SetLimit(VULNERABLE_LIMIT);
}

void BiagiaVulnerable::Start()
{
    _VulnerableTime.Restart();
}

void BiagiaVulnerable::Update(StateMachine& Sm, float Dt)
{
    _VulnerableTime.Update(Dt);
    if(_VulnerableTime.Finished())
    {
        reinterpret_cast<Biagia*>(&Sm)->Shield->Active = true;
        Sm.SetState(BIAGIA_IDLE);
    }
}

// //------------------------------ ------------------------------
// Biagia ::Biagia (const StateInfo& Specs)
// : GenericState(Specs)
// {
// }


// void Biagia ::Start()
// {
// }

// // reinterpret_cast<Biagia*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
// void Biagia ::PhysicsUpdate(StateMachine& Sm, float Dt)
// {
// }

// void Biagia ::OnCollision(StateMachine& Sm, GameObject& Other)
// {
// }
