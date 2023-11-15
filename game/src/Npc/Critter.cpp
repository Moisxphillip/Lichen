#include "Npc/Critter.hpp"
#include "Character/Player.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define BIRD_IDLE SMState::Type01
#define BIRD_FLY SMState::Type02
#define BIRD_PECK SMState::Type03

Bird::Bird(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
}

Bird::~Bird()
{
}

void Bird::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* Sheet = new Sprite(Parent, "./res/img/Npc/BirdSprite.png", 24, 8, 3);
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
    SI = {BIRD_PECK, 16, 3, 0.1, true, true};
    AddState(BIRD_PECK, new BirdPeck(SI));
}

//------------------------------IDLE------------------------------
#define BIRD_BASE_PECK 2.5f
#define BIRD_MIN_DIST 100.f*100.f
#define BIRD_MAX_DIST 700.f*700.f

BirdIdle::BirdIdle(const StateInfo& Specs)
: GenericState(Specs)
{
    _Randomness.seed(42); //TODO Use time seed later
}

void BirdIdle::Start()
{
    _ToPeckTimer.SetLimit(BIRD_BASE_PECK+BIRD_BASE_PECK*_Randomness.gen());
    _ToPeckTimer.Restart();
}

void BirdIdle::Update(StateMachine& Sm, float Dt)
{
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
#define BIRD_FLIGHT_SPEED 280

BirdFly::BirdFly(const StateInfo& Specs)
: GenericState(Specs)
{
    _Init = false;
}

void BirdFly::Update(StateMachine& Sm, float Dt)
{
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
    if(Sm.Parent.Box.Center().DistanceSquared(Player::Self->Parent.Box.Center()) < BIRD_MIN_DIST)
    {
        Sm.SetState(BIRD_FLY);
    }

    _PeckTimer.Update(Dt);
    if(_PeckTimer.Finished())
    {
        Sm.SetState(BIRD_IDLE);
    }

}