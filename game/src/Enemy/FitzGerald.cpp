
#include "Enemy/FitzGerald.hpp"

#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Character/Player.hpp"
#include "Components/AARectangle.hpp"
#include "TestScene.hpp"
#include "Definitions.hpp"
#include "Mechanics/Equipment.hpp"
#include "Core/Input.hpp"
#include "Enemy/Projectile.hpp"
#include "Character/Player.hpp"
#include "Tools/MusicPlayer.hpp"

#define FITZGERALD_IDLE SMState::Type01
#define FITZGERALD_PUNCHDOWN SMState::Type02
#define FITZGERALD_SWIPEDOWN SMState::Type03
#define FITZGERALD_ATTACKHORIZ SMState::Type04
#define FITZGERALD_POSE SMState::Type05
#define FITZGERALD_TELEPORTING SMState::Type06
#define FITZGERALD_TELEPORTED SMState::Type07
#define FITZGERALD_HURT SMState::Type08


#define ENEMY_DEFAULT_INVULNERABILITY 0.4f

FitzGerald* FitzGerald::Self = nullptr;

// class FitzGerald 
FitzGerald::FitzGerald(GameObject& Parent, std::string Label):StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Parent.Represents = ENEMY_MASK;
    Parent.Interacts = PLAYER_ATK_MASK;
    MyStats = Stats{100, 100, 15, 0, 20, 20, 20, 20, 0, 0, 0, 0};
    _HitCooldown.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
    _HitCooldown.Update(ENEMY_DEFAULT_INVULNERABILITY);
    _FlickTime = 0.0f;
    _Flick = false;
    Self = this;
    for(int i = 0; i<5; i++)
    {
        Arena[i] = nullptr;
    }
    if(MusicPlayer::Self)
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/boss.ogg");
    }
}

FitzGerald::~FitzGerald()
{
    Self = nullptr;
    if(Input::Instance().QuitRequested() || Player::Self == nullptr)
    {
        return;
    }

    // Engine::Instance().CurrentScene().Cam.Follow(&(Player::Self->Parent));
    
    //Cleanup Arena
    for(int i = 0; i<5; i++)
    {
        if(Arena[i] != nullptr)
            Arena[i]->RequestDelete();
    }
    if(MusicPlayer::Self)//se der ruim tira
    {
        MusicPlayer::Self->PlaceSong("./res/audio/ost/village.ogg");
    }
}

#define TOTAL_ATTACK_PATTERNS 2
#define FIRST_FASE_NB_ATTACKS 3
#define SECOND_FASE_NB_ATTACKS 5
#define PATTERN_1_ATTACK_DELAY 2
#define PATTERN_2_ATTACK_DELAY .3f

void FitzGerald::SMStart()
{
    Sprite* FitzGerald = new Sprite(Parent, "res/img/boss/fitzgerald_6x6f_158x160px.png", 36, 6, 6, 0.1f);
    FitzGerald->SetScale(2,2);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(FitzGerald->GetWidth(), FitzGerald->GetHeight()));
    AddSprite(FitzGerald);
    MyCollider = new AACircle(Parent, ColliderKind::Trigger, Circle(0,0,FitzGerald->GetHeight()/4));
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {FITZGERALD_IDLE, 0, 6, 0.1f, true, true}; //these are for setting up the spritesheet portion on update
    AddState(FITZGERALD_IDLE, new FitzGeraldIdle(SI));
    SetState(FITZGERALD_IDLE);

    // //Punch state
    SI = {FITZGERALD_PUNCHDOWN, 6, 5, 0.1f, false, true}; //these are for setting up the spritesheet portion on update
    AddState(FITZGERALD_PUNCHDOWN, new FitzGeraldPunchDown(SI));

    // //SwipeDown state
    SI = {FITZGERALD_SWIPEDOWN, 12, 4, 0.1f, false, true}; //these are for setting up the spritesheet portion on update
    AddState(FITZGERALD_SWIPEDOWN, new FitzGeraldSwipeDown(SI));

    // //PunchDownm state
    SI = {FITZGERALD_ATTACKHORIZ, 18, 5, 0.1f, false, true}; //these are for setting up the spritesheet portion on update
    AddState(FITZGERALD_ATTACKHORIZ, new FitzGeraldHorizontalPunch(SI));

    // //Pose state
    SI = {FITZGERALD_POSE, 24, 3, 0.1f, false, true};
    AddState(FITZGERALD_POSE, new FitzGeraldTeleportPose(SI));
    
    // //TPing state
    SI = {FITZGERALD_TELEPORTING, 26, 1, 0.1f, false, true};
    AddState(FITZGERALD_TELEPORTING, new FitzGeraldTeleporting(SI));
    

    ////TPd state
    SI = {FITZGERALD_TELEPORTED, 26, 1, 0.1f, false, true};
    AddState(FITZGERALD_TELEPORTED, new FitzGeraldTeleported(SI));
    
    // //Hurt state
    SI = {FITZGERALD_HURT, 30, 1, 0.0f, false, true};
    AddState(FITZGERALD_HURT, new FitzGeraldHurt(SI));

    AttackPattern = 0;
    RemainingAttacks = FIRST_FASE_NB_ATTACKS;
    

    SetupArena();
}

void FitzGerald::SMUpdate(float Dt)
{
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

void FitzGerald::SetAddColor(Color Color)
{
    _Sections[0].get()->SetAddColor(Color);
}

void FitzGerald::SetScale(Vector2 Scale)
{
    _Sections[0].get()->SetScale(Scale);
}

#include "Tools/ElementLoader.hpp"
void FitzGerald::SMOnCollision(GameObject& Other)
{
        
    if (_CurrState != FITZGERALD_HURT && !Parent.IsDead() && Other.Contains(COMPONENT_ATTACK) 
        && static_cast<bool>(Other.Represents & PLAYER_ATK_MASK) && _HitCooldown.Finished())
    {
        Attack* Atk = (Attack*)Other.GetComponent(COMPONENT_ATTACK);
        int Dmg = Combat::CalculateDamage(Atk->Attacker, Atk->Data, MyStats, Parent.Box.Center());
        if(MyStats.HP <= 0)
        {
            // SetState(_DEATH);
            // GameObject* Drop = new GameObject();
            // Drop->Depth = DepthMode::Dynamic;
            // Drop->AddComponent(new Equipment(*Drop));
            // Drop->Box.SetCenter(Parent.B8ox.Center());
            // Engine::Instance().CurrentScene().AddGameObj(Drop);
            int i = Engine::RandomUint()%3;
            switch(i)
            {
                case 0:
                    FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/boss/mage3_hurt1.wav", 20);
                    break;
                case 1:
                    FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/boss/mage3_hurt2.wav", 20);
                    break;
                case 2:
                    FastCreate::PlayPanOnce(Parent.Box.Center(), "./res/audio/boss/mage3_hurt3.wav", 20);
                    break;
                default:
                    break;
            }
            if(Player::Self != nullptr)
            {
                Player::Self->AddExperience(Combat::DeathExp(MyStats.Level)*2);
            }
            Parent.RequestDelete();
            return;
        }
        SetState(FITZGERALD_HURT);
        MyCollider->ApplyForce(Other.Box.Center().DistVector2(Parent.Box.Center()).Normalized() * Atk->Data.Knockback * 50000);
        MyCollider->SetFriction(0.05f);
        _HitCooldown.Restart();
    }

}
void FitzGerald::SetupArena()
{

    for(int i = 0; i<5; i++)
    {
        Arena[i] = new GameObject();
        Arena[i]->Represents = CollisionMask::Terrain;
        Arena[i]->Depth = DepthMode::Foreground;
    }
    
    GameObject* Go = new GameObject();
    Go->AddComponent(new Sprite(*Go,"./res/img/tile/arena.png"));
    Go->Box.Redimension(Vector2(1280,720));
    Engine::Instance().CurrentScene().AddGameObj(Go);

    Vector2 Center = Parent.Box.Center();
    //Colliders
    Arena[0]->AddComponent(new AARectangle(*Arena[0], ColliderKind::Stationary, Rectangle(0,0,1280, 128)));
    Arena[0]->Box.SetPosition(Center - Vector2(0, 360+32));

    Arena[1]->AddComponent(new AARectangle(*Arena[1], ColliderKind::Stationary, Rectangle(0,0,1280, 64)));
    Arena[1]->Box.SetPosition(Center + Vector2(0, 360+32));

    Arena[2]->AddComponent(new AARectangle(*Arena[2], ColliderKind::Stationary, Rectangle(0,0,64, 720)));
    Arena[2]->Box.SetPosition(Center - Vector2(640+32, 0));

    Arena[3]->AddComponent(new AARectangle(*Arena[3], ColliderKind::Stationary, Rectangle(0,0,64, 720)));
    Arena[3]->Box.SetPosition(Center + Vector2(640+32, 0));

    // New Focal center
    Arena[4]->Box.SetPosition(Parent.Box.Center());
    // Engine::Instance().CurrentScene().Cam.Follow(Arena[4]);
    Engine::Instance().CurrentScene().Cam.Follow(Go);
    Go->Box.SetCenter(Arena[4]->Box.Position());

    for(int i = 0; i<5; i++)
    {
        Engine::Instance().CurrentScene().AddGameObj(Arena[i]);
    }
}

#define MOVIMENTATION_SPEED 150

void FitzGerald::MoveTo(Vector2 Destiny, float Dt)
{
    Destiny.x < Parent.Box.Center().x ? SetFlip(Flip::N) : SetFlip(Flip::H);
    Vector2 Distance = Parent.Box.Center().DistVector2(Destiny);
    if(Distance.Magnitude()< 10)
    {
        return;
    }
    // For now the enemy is teleporting, leave it commented
    // if(Distance.MagnitudeSquared() < MOVE_SPD*MOVE_SPD *Dt)
    // {
    //     Parent.Box.SetCenter(Destiny);
    // }

    MyCollider->ApplyForce(Distance.Normalized()*MOVIMENTATION_SPEED); 
}



//------------------------------TELEPORTPOSE------------------------------





FitzGeraldIdle::FitzGeraldIdle(const StateInfo& Specs)
: GenericState(Specs)
{

}

void FitzGeraldIdle::Start()
{
    _Started = false;
}

void FitzGeraldIdle::Update(StateMachine& Sm, float Dt)
{
    FitzGerald* FG = reinterpret_cast<FitzGerald*>(&Sm);
    if(!_Started)
    {
        if(FG->AttackPattern == 0)
        {
            _AttackDelay.SetLimit(PATTERN_1_ATTACK_DELAY);
        }
        else
        {
            _AttackDelay.SetLimit(PATTERN_2_ATTACK_DELAY);
        }
        

        _Started = true;
    }



     _AttackDelay.Update(Dt);
    

    if(!_AttackDelay.Finished())
    {
        FG->MoveTo(FG->Arena[4]->Box.Position(), Dt);
    }
    else
    {
        FG->MyCollider->SetVelocity(Vector2::ZERO);
        if(FG->AttackPattern == 0 && FG->RemainingAttacks > 0)
        {
            float Rnd = Engine::RandomFloat();
    
            if(Rnd < 0.5)
            {
                FG->NextState = FITZGERALD_PUNCHDOWN;
            }
            else
            {
                FG->NextState = FITZGERALD_SWIPEDOWN;
            }

            FG->RemainingAttacks--;

            
        }
        else if(FG->AttackPattern == 0)
        {
            FG->AttackPattern = 1;
            FG->RemainingAttacks = 3;

            _AttackDelay.SetLimit(PATTERN_2_ATTACK_DELAY );

        }
        else if(FG->AttackPattern == 1 && FG->RemainingAttacks > 0)
        {
            FG->NextState = FITZGERALD_ATTACKHORIZ;
            FG->RemainingAttacks--;
        }
        else if(FG->AttackPattern == 1 )
        {
            FG->RemainingAttacks = 3;
            FG->AttackPattern = 0;

            _AttackDelay.SetLimit(PATTERN_1_ATTACK_DELAY );
        }
        _AttackDelay.Restart();
        Sm.SetState(FITZGERALD_POSE);
    }
}


//------------------------------PUNCHDOWN------------------------------

#define PUNCH_DOWN_ATACK 1.0f
#define PUNCH_DOWN_ATACK_POINT 0.2f

FitzGeraldPunchDown::FitzGeraldPunchDown(const StateInfo& Specs)
: GenericState(Specs)
{
    _HasAttacked = false;
    // TODO mudar
    _AtkTime.SetLimit(PUNCH_DOWN_ATACK); 
}

void FitzGeraldPunchDown::Start()
{
    _AtkTime.Restart();
}

void FitzGeraldPunchDown::Update(StateMachine& Sm, float Dt)
{
    _AtkTime.Update(Dt);
    FitzGerald* FG = reinterpret_cast<FitzGerald*>(&Sm);


    if(!_HasAttacked && Player::Self && _AtkTime.Get() >= PUNCH_DOWN_ATACK_POINT)
    {
        FG->MyCollider->SetVelocity(Vector2::ZERO);
    
        GameObject* Atk = new GameObject;
        Atk->Represents = ENEMY_ATK_MASK;

        Vector2 Direction = FG->Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());

        Atk->Box.SetCenter(FG->Parent.Box.Center() + Vector2(0.f, 60.0f));
        Atk->AddComponent(new Attack(*Atk, FG->MyStats, {10, 1, ScalingStats::Strength}, FG->Parent.Interacts, 0.3));
        AARectangle* Rect = new AARectangle(*Atk, ColliderKind::Trigger, Rectangle(0,0, 60, 160));
        Rect->SetFriction(0.0f);
        Atk->AddComponent(Rect);

        Engine::Instance().CurrentScene().AddGameObj(Atk);

        _HasAttacked = true;
    }

    if(_AtkTime.Finished())
    {
        Sm.SetState(FITZGERALD_IDLE);
        _AtkTime.Restart();
        _HasAttacked = false;
        return;
    }
}

//------------------------------SWIPEDOWN------------------------------
#define SWIPE_DOWN_ATACK 1.2f
#define SWIPE_DOWN_ATACK_POINT 0.2f


FitzGeraldSwipeDown::FitzGeraldSwipeDown(const StateInfo& Specs)
: GenericState(Specs)
{
    _HasAttacked = false;
    // TODO mudar
    _AtkTime.SetLimit(SWIPE_DOWN_ATACK); 
}

void FitzGeraldSwipeDown::Start()
{
     _AtkTime.Restart();
}

void FitzGeraldSwipeDown::Update(StateMachine& Sm, float Dt)
{

    _AtkTime.Update(Dt);
    FitzGerald* FG = reinterpret_cast<FitzGerald*>(&Sm);

    if(!_HasAttacked && Player::Self)
    {
        Player::Self->Parent.Box.Center().x < FG->Parent.Box.Center().x ? FG->SetFlip(Flip::N) : FG->SetFlip(Flip::H);
    }


    if(!_HasAttacked && Player::Self && _AtkTime.Get() >= SWIPE_DOWN_ATACK_POINT)
    {
        FG->MyCollider->SetVelocity(Vector2::ZERO);
    
        GameObject* Atk = new GameObject;
        Atk->Represents = ENEMY_ATK_MASK;

        Vector2 Direction = FG->Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());

        Atk->Box.SetCenter(FG->Parent.Box.Center() + Vector2(Direction.x/std::fabs(Direction.x) *40.0f, 30.0f));
        Atk->AddComponent(new Attack(*Atk, FG->MyStats, {10, 1, ScalingStats::Strength}, FG->Parent.Interacts, 0.3));
        AACircle* Ball = new AACircle(*Atk, ColliderKind::Trigger, Circle(0,0, 120));
        Ball->SetFriction(0.0f);
        Atk->AddComponent(Ball);

        Engine::Instance().CurrentScene().AddGameObj(Atk);

        _HasAttacked = true;
    }

    if(_AtkTime.Finished())
    {
        Sm.SetState(FITZGERALD_IDLE);
        _AtkTime.Restart();
        _HasAttacked = false;
        return;
    }
}


//------------------------------HORIZONTALPUNCH------------------------------

#define HORIZONTAL_ATACK .6f
#define HORIZONTAL_ATACK_POINT .2f

FitzGeraldHorizontalPunch::FitzGeraldHorizontalPunch(const StateInfo& Specs)
: GenericState(Specs)
{
    _HasAttacked = false;
    // TODO mudar
    _AtkTime.SetLimit(HORIZONTAL_ATACK); 
}
void FitzGeraldHorizontalPunch::Start()
{
    _AtkTime.Restart();
}
void FitzGeraldHorizontalPunch::Update(StateMachine& Sm, float Dt)
{
    

    _AtkTime.Update(Dt);
    FitzGerald* FG = reinterpret_cast<FitzGerald*>(&Sm);

    if(!_HasAttacked && Player::Self)
    {
        Player::Self->Parent.Box.Center().x < FG->Parent.Box.Center().x ? FG->SetFlip(Flip::H) : FG->SetFlip(Flip::N);
    }


    if(!_HasAttacked && Player::Self && _AtkTime.Get() >= PUNCH_DOWN_ATACK_POINT)
    {
        FG->MyCollider->SetVelocity(Vector2::ZERO);
    
        GameObject* Atk = new GameObject;
        Atk->Represents = ENEMY_ATK_MASK;

        Vector2 Direction = FG->Parent.Box.Center().DistVector2(Player::Self->Parent.Box.Center());

        Atk->Box.SetCenter(FG->Parent.Box.Center() + Vector2(Direction.x/std::fabs(Direction.x) *80.0f, -20.0f));
        Atk->AddComponent(new Attack(*Atk, FG->MyStats, {10, 1, ScalingStats::Strength}, FG->Parent.Interacts, 0.3));
        AARectangle* Rect = new AARectangle(*Atk, ColliderKind::Trigger, Rectangle(0,0, 160, 90));
        Rect->SetFriction(0.0f);
        Atk->AddComponent(Rect);

        Engine::Instance().CurrentScene().AddGameObj(Atk);

        _HasAttacked = true;
    }

    if(_AtkTime.Finished())
    {
        Sm.SetState(FITZGERALD_IDLE);
        _AtkTime.Restart();
        _HasAttacked = false;
        return;
    }
}

//------------------------------TELEPORTPOSE------------------------------

#define TELEPORT_TIME 0.3f

FitzGeraldTeleportPose::FitzGeraldTeleportPose(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void FitzGeraldTeleportPose::Start()
{
    _Started = false;
    _Tp.Restart();
    
}
void FitzGeraldTeleportPose::Update(StateMachine& Sm, float Dt)
{
    if(!_Started)
    {
        reinterpret_cast<FitzGerald*>(&Sm)->SetAddColor(Color("#990099"));
    }
    _Tp.Update(Dt);
    if(_Tp.Finished())
    {
        Sm.SetState(FITZGERALD_TELEPORTING);
    }
}

//------------------------------TELEPORTING------------------------------

FitzGeraldTeleporting::FitzGeraldTeleporting(const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME);
}

void FitzGeraldTeleporting::Start()
 {
    _Tp.Restart();
}

void FitzGeraldTeleporting::Update(StateMachine& Sm, float Dt)
{
    FitzGerald* FG = reinterpret_cast<FitzGerald*>(&Sm);

   

    _Tp.Update(Dt);

    reinterpret_cast<FitzGerald*>(&Sm)->SetScale(Vector2(2-(_Tp.Get()/(TELEPORT_TIME+0.1f)*2),2.f));


    if(_Tp.Finished())
    {   
        if((FG->NextState == FITZGERALD_PUNCHDOWN || FG->NextState == FITZGERALD_SWIPEDOWN) && Player::Self)
        {
            FG->MyCollider->Position = Player::Self->Parent.Box.Center() - Vector2(0, 100);     
        }
        else if(FG->NextState == FITZGERALD_ATTACKHORIZ && Player::Self)
        { 
            float Rnd = Engine::RandomFloat();
    
            if(Rnd < 0.5)
            {
                FG->MyCollider->Position = Player::Self->Parent.Box.Center() - Vector2(-60, 0);   
            }
            else
            {
                FG->MyCollider->Position = Player::Self->Parent.Box.Center() - Vector2(60, 0);   
            }
        }
           
        Sm.SetState(FITZGERALD_TELEPORTED);
    }
}


//------------------------------TELEPORTED------------------------------

FitzGeraldTeleported::FitzGeraldTeleported (const StateInfo& Specs)
: GenericState(Specs)
{
    _Tp.SetLimit(TELEPORT_TIME+0.1f);
}

void FitzGeraldTeleported::Start()
{
    _Tp.Restart();
}

void FitzGeraldTeleported::Update(StateMachine& Sm, float Dt)
{
     _Tp.Update(Dt);

    reinterpret_cast<FitzGerald*>(&Sm)->SetScale(Vector2(_Tp.Get()/(TELEPORT_TIME+0.1f)*2,2.f));

    if(_Tp.Finished())
    {
        reinterpret_cast<FitzGerald*>(&Sm)->SetAddColor(Color("#000000"));
        Sm.SetState(reinterpret_cast<FitzGerald*>(&Sm)->NextState);
    }
}



//------------------------------HURT ------------------------------

FitzGeraldHurt::FitzGeraldHurt (const StateInfo& Specs)
: GenericState(Specs)
{
    _HurtTime.SetLimit(ENEMY_DEFAULT_INVULNERABILITY);
}
void FitzGeraldHurt::Start()
{
    _HurtTime.Restart();
}
void FitzGeraldHurt::Update(StateMachine& Sm, float Dt)
{
    _HurtTime.Update(Dt);
    if(_HurtTime.Finished())
    {
        Sm.SetState(FITZGERALD_IDLE);
    }
}
void FitzGeraldHurt::PhysicsUpdate(StateMachine& Sm, float Dt)
{

}
void FitzGeraldHurt::OnCollision(StateMachine& Sm, GameObject& Other)
{

}
