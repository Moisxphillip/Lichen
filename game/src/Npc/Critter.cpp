#include "Npc/Critter.hpp"
#include "Character/Player.hpp"
#include "Tools/DistanceTrigger.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define BIRD_IDLE SMState::Type01
#define BIRD_FLY SMState::Type02
#define BIRD_PECK SMState::Type03

int Critter::MaxCritterCount = 20;
int Critter::CritterCount = 0;

Bird::Bird(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    Critter::CritterCount++;
}

Bird::~Bird()
{
    Critter::CritterCount--;
}

void Bird::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/npc/bird_8x3f.png", 24, 8, 3);
    Sheet->SetScale(Vector2(2,2));
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    AddSprite(Sheet);
    
    //Idle
    StateInfo SI = {BIRD_IDLE, 0, 2, 0.3, true, true}; //these are for setting up the spritesheet portion on update
    AddState(BIRD_IDLE, new BirdIdle(SI));
    SetState(BIRD_IDLE);

    //Fly
    SI = {BIRD_FLY, 8, 8, 0.06, true, true};
    AddState(BIRD_FLY, new BirdFly(SI));
    
    //Peck
    SI = {BIRD_PECK, 16, 6, 0.1, true, true};
    AddState(BIRD_PECK, new BirdPeck(SI));
    
    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
}

//------------------------------IDLE------------------------------
#define BIRD_BASE_PECK 2.5f
#define BIRD_MIN_DIST 100.f*100.f
#define BIRD_MAX_DIST 700.f*700.f

#include <ctime>

BirdIdle::BirdIdle(const StateInfo& Specs)
: GenericState(Specs)
{
    _Randomness.seed(static_cast<unsigned long long int>(std::time(nullptr)));
}

void BirdIdle::Start()
{
    _ToPeckTimer.SetLimit(BIRD_BASE_PECK+BIRD_BASE_PECK*_Randomness.gen());
    _ToPeckTimer.Restart();
}

void BirdIdle::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) < BIRD_MIN_DIST)
    {
        Sm.SetState(BIRD_FLY);
    }

    _ToPeckTimer.Update(Dt);
    if(_ToPeckTimer.Finished())
    {
        Sm.SetState(BIRD_PECK);
    }
}

//------------------------------FLY------------------------------
#define BIRD_FLIGHT_SPEED 300

BirdFly::BirdFly(const StateInfo& Specs)
: GenericState(Specs)
{
    _Init = false;
}

void BirdFly::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(!_Init)
    {
        _Direction = Player::Self->Parent.Box.Center().DistVector2(Sm.Parent.Box.Center()).Normalized();
        Sm.SetFlip(_Direction.x > 0.0f ? Flip::H : Flip::N);
        _Init = true;
    }

    Sm.Parent.Box+=_Direction*BIRD_FLIGHT_SPEED*Dt;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) > BIRD_MAX_DIST)
    {
        Sm.Parent.RequestDelete();
    }
}

//------------------------------PECK------------------------------
#define BIRD_PECK_TIME 0.3f
#include "Core/Engine.hpp"


BirdPeck::BirdPeck(const StateInfo& Specs)
: GenericState(Specs)
{
    _PeckTimer.SetLimit(BIRD_PECK_TIME);
}

void BirdPeck::Start()
{
    
    _PeckTimer.Restart();
}

void BirdPeck::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) < BIRD_MIN_DIST)
    {
        Sm.SetState(BIRD_FLY);
    }

    _PeckTimer.Update(Dt);
    if(_PeckTimer.Finished())
    {
        Sm.SetFlip(Engine::RandomUint() & 1 ? Flip::H : Flip::N);
        Sm.SetState(BIRD_IDLE);
    }

}


//Define names for the SMState enums, so it's easier to know which state you're using
#define WORM_IDLE SMState::Type01
#define WORM_FLEE SMState::Type02

Worm::Worm(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    Critter::CritterCount++;
}

Worm::~Worm()
{
    Critter::CritterCount--;
}

void Worm::SMStart()
{
    // Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/npc/worm_5x1f_15x15px.png", 6, 6, 1);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    AddSprite(Sheet);
    
    //Idle
    StateInfo SI = {WORM_IDLE, 0, 2, 0.5, true, true}; //these are for setting up the spritesheet portion on update
    AddState(WORM_IDLE, new WormIdle(SI));
    SetState(WORM_IDLE);

    //Flee
    SI = {WORM_FLEE, 0, 6, 0.1, true, true};
    AddState(WORM_FLEE, new WormFlee(SI));
    
    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
}

//------------------------------IDLE------------------------------
#define WORM_MIN_DIST 100.f*100.f
#define WORM_MAX_DIST 700.f*700.f

WormIdle::WormIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void WormIdle::Start()
{
}

void WormIdle::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) < WORM_MIN_DIST)
    {
        Sm.SetState(WORM_FLEE);
    }
}

//------------------------------FLEE------------------------------
#define WORM_SPEED 100

WormFlee::WormFlee(const StateInfo& Specs)
: GenericState(Specs)
{
    _Init = false;
}

void WormFlee::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(!_Init)
    {
        _Direction = Player::Self->Parent.Box.Center().DistVector2(Sm.Parent.Box.Center()).Normalized();
        Sm.SetFlip(_Direction.x > 0.0f ? Flip::H : Flip::N);
        _Init = true;
    }

    Sm.Parent.Box+=_Direction*WORM_SPEED*Dt;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) > WORM_MAX_DIST)
    {
        Sm.Parent.RequestDelete();
    }
}












//Define names for the SMState enums, so it's easier to know which state you're using
#define FUNGI_IDLE SMState::Type01
#define FUNGI_FLEE SMState::Type02

SmallFungi::SmallFungi(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    Critter::CritterCount++;
}

SmallFungi::~SmallFungi()
{
    Critter::CritterCount--;
}

void SmallFungi::SMStart()
{
    // Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/npc/tinyshroom_4x3f_20x18px.png", 12, 4, 3);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(Sheet->GetWidth(), Sheet->GetHeight()));
    AddSprite(Sheet);
    
    //Idle
    StateInfo SI = {FUNGI_IDLE, 8, 4, 0.2, true, true}; //these are for setting up the spritesheet portion on update
    AddState(FUNGI_IDLE, new SmallFungiIdle(SI));
    SetState(FUNGI_IDLE);

    //Flee
    SI = {FUNGI_FLEE, 4, 4, 0.2, true, true};
    AddState(FUNGI_FLEE, new SmallFungiFlee(SI));

    Parent.AddComponent(new DistanceTrigger(Parent, this, 2560, DistTriggerMode::Delete));
}

//------------------------------IDLE------------------------------
#define FUNGI_MIN_DIST 130.f*130.f
#define FUNGI_MAX_DIST 700.f*700.f

SmallFungiIdle::SmallFungiIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void SmallFungiIdle::Start()
{
}

void SmallFungiIdle::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) < FUNGI_MIN_DIST)
    {
        Sm.SetState(FUNGI_FLEE);
    }
}

//------------------------------FLEE------------------------------
#define FUNGI_SPEED 200

SmallFungiFlee::SmallFungiFlee(const StateInfo& Specs)
: GenericState(Specs)
{
    _Init = false;
}

void SmallFungiFlee::Update(StateMachine& Sm, float Dt)
{
    if(Player::Self == nullptr) return;
    if(!_Init)
    {
        _Direction = Player::Self->Parent.Box.Center().DistVector2(Sm.Parent.Box.Center()).Normalized();
        Sm.SetFlip(_Direction.x > 0.0f ? Flip::H : Flip::N);
        _Init = true;
    }

    Sm.Parent.Box+=_Direction*FUNGI_SPEED*Dt;
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) > FUNGI_MAX_DIST)
    {
        Sm.Parent.RequestDelete();
    }
}
