#include "Enemy/Malachi.hpp"

#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Character/Player.hpp"
#include "Components/AARectangle.hpp"
#include "TestScene.hpp"
#include "Definitions.hpp"
#include "Mechanics/Equipment.hpp"
#include "Core/Input.hpp"
#include "Enemy/Projectile.hpp"


//Define names for the SMState enums, so it's easier to know which state you're using
#define MALACHI_IDLE SMState::Type01
#define MALACHI_ATTACKDOWN SMState::Type02
#define MALACHI_ATTACKHORIZ SMState::Type03
#define MALACHI_POSE SMState::Type04
#define MALACHI_TELEPORTING SMState::Type05
#define MALACHI_TELEPORTED SMState::Type06
#define MALACHI_HURT SMState::Type07
#define MALACHI_VULNERABLE SMState::Type08


#define ENEMY_DEFAULT_INVULNERABILITY 0.4f

Malachi* Malachi::Self = nullptr;

#include "Tools/MusicPlayer.hpp"

Malachi::Malachi(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Parent.Represents = ENEMY_MASK;
    Parent.Interacts = REFLECTED_BULLET_MASK | PLAYER_ATK_MASK;
    MyStats = Stats{100, 100, 5, 0, 10, 10, 10, 10, 0, 0, 0, 0};
    _HitCooldown.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
    _HitCooldown.Update(ENEMY_DEFAULT_INVULNERABILITY);
    _FlickTime = 0.0f;
    _Flick = false;
    Self = this;
    Shield = nullptr;
    if(MusicPlayer::Self)
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/boss.ogg");
    }

    for(int i = 0; i<5; i++)
    {
        Arena[i] = nullptr;
    }
}

Malachi::~Malachi()
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
    if(MusicPlayer::Self)
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/village.ogg");
    }
}

// #define MALACHI_DEFAULT_FRICTION 0.1f
void Malachi::SMStart()
{
    Sprite* malachi = new Sprite(Parent, "./res/img/boss/malachi_6x9f_110x109px.png", 54, 6, 9, 0.1f);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(malachi->GetWidth(), malachi->GetHeight()));
    AddSprite(malachi);
    MyCollider = new AACircle(Parent, ColliderKind::Trigger, Circle(0,0,malachi->GetHeight()/4));
    // MyCollider->SetFriction(MALACHI_DEFAULT_FRICTION);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {MALACHI_IDLE, 0, 6, 0.1f, true, true}; //these are for setting up the spritesheet portion on update
    AddState(MALACHI_IDLE, new MalachiIdle(SI));
    SetState(MALACHI_IDLE);

    //AtkDown state
    SI = {MALACHI_ATTACKDOWN, 6, 3, 0.1f, false, true};
    AddState(MALACHI_ATTACKDOWN, new MalachiAtkDown(SI));
    
    //AtkHoriz state
    SI = {MALACHI_ATTACKHORIZ, 18, 3, 0.1f, false, true};
    AddState(MALACHI_ATTACKHORIZ, new MalachiAtkHoriz(SI));
    
    //Pose state
    SI = {MALACHI_POSE, 24, 3, 0.1f, false, true};
    AddState(MALACHI_POSE, new MalachiTeleportPose(SI));
    
    //TPing state
    SI = {MALACHI_TELEPORTING, 30, 3, 0.1f, false, true};
    AddState(MALACHI_TELEPORTING, new MalachiTeleporting(SI));
    
    //TPd state
    SI = {MALACHI_TELEPORTED, 36, 4, 0.1f, false, true};
    AddState(MALACHI_TELEPORTED, new MalachiTeleported(SI));
    
    //Hurt state
    SI = {MALACHI_HURT, 42, 1, 0.0f, false, true};
    AddState(MALACHI_HURT, new MalachiHurt(SI));
    
    //Vulnerable state
    SI = {MALACHI_VULNERABLE, 48, 3, 0.1f, true, true};
    AddState(MALACHI_VULNERABLE, new MalachiVulnerable(SI));

    SetupArena();
    GameObject* Sh = new GameObject();
    Sh->Depth = DepthMode::Dynamic;
    Shield = new Sprite(*Sh, "./res/img/boss/bubble.png", 4, 4, 1);
    Sh->Box.Redimension(Vector2(Shield->GetWidth(), Shield->GetHeight()));
    Sh->AddComponent(Shield);
    Engine::Instance().CurrentScene().AddGameObj(Sh);
}

void Malachi::SMUpdate(float Dt)
{
    if(Shield != nullptr && Shield->Active)
    {
        Shield->Parent.Box.SetCenter(Parent.Box.Center());
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
#include "Tools/ElementLoader.hpp"
void Malachi::SMOnCollision(GameObject& Other)
{

    if(_CurrState != MALACHI_VULNERABLE && static_cast<bool>(Other.Represents & REFLECTED_BULLET_MASK))
    {
        Shield->Active = false;
        SetState(MALACHI_VULNERABLE);

        GameObject* Sh = new GameObject();
        Sh->Depth = DepthMode::Dynamic;
        Sprite* Shieldn = new Sprite(*Sh, "./res/img/boss/bubble.png", 4, 4, 1, 0.1, 0.4);
        Sh->Box.Redimension(Vector2(Shieldn->GetWidth(), Shieldn->GetHeight()));
        Sh->Box.SetCenter(Parent.Box.Center());
        Sh->AddComponent(Shieldn);
        Engine::Instance().CurrentScene().AddGameObj(Sh);
    }
    else if (_CurrState == MALACHI_VULNERABLE && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) 
        && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK) && _HitCooldown.Finished())
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats, Parent.Box.Center());

        int i = Engine::RandomUint()%2;
        switch(i)
        {
            case 0:
                FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/boss/mage1_hurt1.wav", 20);
                break;
            case 1:
                FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/boss/mage1_hurt2.wav", 20);
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
        // SetState(MALACHI_HURT);
        // MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        // MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }
}

void Malachi::SetupArena()
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

void Malachi::Shoot()
{
    int Max = 3+ Engine::RandomUint()%3;
    for(int i = 0; i<Max; i++)
    {
    GameObject* Blt = new GameObject();
    Blt->Depth = DepthMode::Dynamic;
    Blt->Represents = ENEMY_ATK_MASK;
    Sprite* Sprt = new Sprite(*Blt, "./res/img/boss/spark.png", 7, 7, 1, 0.1f);
    Blt->Box.Redimension(Vector2(Sprt->GetWidth(), Sprt->GetHeight()));
    Blt->AddComponent(Sprt);
    Vector2 Dir = Player::Self != nullptr ?  Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center()).Normalized() : Vector2(1, 0);
    Dir.Rotate((Engine::RandomFloat() - 0.5f)*1.5f);
    Vector2 Offset = Dir * 100;
    Blt->Box.SetPosition(Parent.Box.Center() + Offset);
    Blt->AddComponent(new Projectile(*Blt, Dir*2.0f, Sprt->GetWidth()/3, PLAYER_ATK_MASK | PLAYER_MASK));
    Blt->AddComponent(new Attack(*Blt, MyStats, {MyStats.Int*2, 1, ScalingStats::Intelect},
        Blt->Interacts, 20.0f));
    Engine::Instance().CurrentScene().AddGameObj(Blt);
    }
}
//------------------------------IDLE------------------------------


#define IDLE_TIME 1.0f

MalachiIdle::MalachiIdle(const StateInfo& Specs)
: GenericState(Specs)
{
    _TeleportChance = 50;
    _ShootChance = 50;
    _ChangeState.SetLimit(IDLE_TIME + 0.5*Engine::RandomFloat());
}

void MalachiIdle::Start()
{
    _ChangeState.SetLimit(IDLE_TIME + 0.5*Engine::RandomFloat());
    _ChangeState.Restart();
}

void MalachiIdle::Update(StateMachine& Sm, float Dt)
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
    
    if(Rnd < Tp)
    {
        _ShootChance+=10;
        _TeleportChance-=10;
        Sm.SetState(MALACHI_POSE);
    }
    else
    {
        _ShootChance-=10;
        _TeleportChance+=10;
        Vector2 Dist = Sm.Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());
        Dist.x > 0.0f ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
        Dist.y > std::abs(Dist.x) ? Sm.SetState(MALACHI_ATTACKDOWN) : Sm.SetState(MALACHI_ATTACKHORIZ);
    }

    // if(Engine::RandomUint() & 1)
    // {
    //     Vector2 Dist = Sm.Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());
    //     Dist.x > 0.0f ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
    //     Dist.y > std::abs(Dist.x) ? Sm.SetState(MALACHI_ATTACKDOWN) : Sm.SetState(MALACHI_ATTACKHORIZ);
    //     return;
    // }
}

//------------------------------ATKDOWN------------------------------
MalachiAtkDown::MalachiAtkDown (const StateInfo& Specs)
: GenericState(Specs)
{
    _AtkTime.SetLimit(0.5f);
}


void MalachiAtkDown::Start()
{
    _AtkTime.Restart();
    int i = Engine::RandomUint()%2;
    switch(i)
    {
        case 0:
            FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage1_shoot1.wav", 20);
            break;
        case 1:
            FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage1_shoot2.wav", 20);
            break;
        default:
            break;
    }
}

void MalachiAtkDown::Update(StateMachine& Sm, float Dt)
{
    _AtkTime.Update(Dt);
    if(_AtkTime.Finished())
    {
        
        reinterpret_cast<Malachi*>(&Sm)->Shoot();
        Sm.SetState(MALACHI_IDLE);
    }
}

//------------------------------ATKHORIZ------------------------------
MalachiAtkHoriz::MalachiAtkHoriz(const StateInfo& Specs)
: GenericState(Specs)
{
    _AtkTime.SetLimit(0.5f);
}


void MalachiAtkHoriz::Start()
{
    int i = Engine::RandomUint()%2;
    switch(i)
    {
        case 0:
            FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage1_shoot1.wav", 20);
            break;
        case 1:
            FastCreate::PlayPanOnce(Vector2::ZERO, "./res/audio/boss/mage1_shoot2.wav", 20);
            break;
        default:
            break;
    }
    _AtkTime.Restart();
}

// reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void MalachiAtkHoriz::Update(StateMachine& Sm, float Dt)
{
    _AtkTime.Update(Dt);
    if(_AtkTime.Finished())
    {
        reinterpret_cast<Malachi*>(&Sm)->Shoot();
        Sm.SetState(MALACHI_IDLE);
    }
}


//------------------------------TELEPORTPOSE------------------------------
#define TELEPORT_TIME 0.3f

MalachiTeleportPose::MalachiTeleportPose (const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void MalachiTeleportPose::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 

void MalachiTeleportPose::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Sm.SetState(MALACHI_TELEPORTING);
    }
}


//------------------------------TELEPORTING------------------------------
MalachiTeleporting::MalachiTeleporting(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void MalachiTeleporting::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void MalachiTeleporting::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Malachi* Mm = reinterpret_cast<Malachi*>(&Sm);
        Mm->MyCollider->Position = Mm->Arena[4]->Box.Position() 
            + Vector2(1000 * (Engine::RandomFloat()-0.5f), 500 * (Engine::RandomFloat()-0.5f));        
        Sm.SetState(MALACHI_TELEPORTED);
    }
}



//------------------------------ ------------------------------
MalachiTeleported::MalachiTeleported(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME+0.1f);
}

void MalachiTeleported::Start()
{
    _Tp.Restart();
}

// reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void MalachiTeleported::Update(StateMachine& Sm, float Dt)
{
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Sm.SetState(MALACHI_IDLE);
    }
}


//------------------------------HURT------------------------------
MalachiHurt::MalachiHurt(const StateInfo& Specs)
: GenericState(Specs)
{
}


void MalachiHurt::Start()
{
}

// reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
void MalachiHurt::Update(StateMachine& Sm, float Dt)
{
}

void MalachiHurt::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void MalachiHurt::OnCollision(StateMachine& Sm, GameObject& Other)
{
}

//------------------------------VULNERABLE------------------------------
#define VULNERABLE_LIMIT 4.0f

MalachiVulnerable::MalachiVulnerable (const StateInfo& Specs)
: GenericState(Specs)
{
    _VulnerableTime.SetLimit(VULNERABLE_LIMIT);
}

void MalachiVulnerable::Start()
{
    _VulnerableTime.Restart();
}

void MalachiVulnerable::Update(StateMachine& Sm, float Dt)
{
    _VulnerableTime.Update(Dt);
    if(_VulnerableTime.Finished())
    {
        reinterpret_cast<Malachi*>(&Sm)->Shield->Active = true;
        Sm.SetState(MALACHI_IDLE);
    }
}

// //------------------------------ ------------------------------
// Malachi ::Malachi (const StateInfo& Specs)
// : GenericState(Specs)
// {
// }


// void Malachi ::Start()
// {
// }

// // reinterpret_cast<Malachi*>(&Sm)->MoveTo(Player::Self->Parent.Box.Center()+Vector2(0,32), Dt); 
// void Malachi ::PhysicsUpdate(StateMachine& Sm, float Dt)
// {
// }

// void Malachi ::OnCollision(StateMachine& Sm, GameObject& Other)
// {
// }
