#include "Dummy.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define DUMMY_IDLE SMState::Type01
#define DUMMY_WALK SMState::Type02

Dummy::Dummy(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
}

void Dummy::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* galo = new Sprite(Parent, "./res/galor.png");
    Parent.Depth = DepthMode::Foreground;
    Parent.Box.Redimension(Vector2(galo->GetWidth(), galo->GetHeight()));
    AddSprite(galo);

    
    //Create an idle state
    StateInfo SI = {DUMMY_IDLE, 0,1,0,false, true}; //these are for setting up the spritesheet portion on update
    DummyIdle* Dummy = new DummyIdle(SI);
    AddState(DUMMY_IDLE, Dummy);
    SetState(DUMMY_IDLE);

    //Create a walk state
    SI = {DUMMY_WALK, 0,1,0,false, true};
    DummyWalk* Dum = new DummyWalk(SI);
    AddState(DUMMY_WALK, Dum);
}


//------------------------------IDLE------------------------------

DummyIdle::DummyIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void DummyIdle::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);

    if(x!=0 ||y !=0)//condition for changing to walk state
    {
        Sm.SetState(DUMMY_WALK);
        return;
    }
}

//------------------------------WALK------------------------------
DummyWalk::DummyWalk(const StateInfo& Specs)
: GenericState(Specs)
{
}

void DummyWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();

    int x = Ip.KeyPressedDown(Key::D) - Ip.KeyPressedDown(Key::A);
    int y = Ip.KeyPressedDown(Key::S) - Ip.KeyPressedDown(Key::W);
    
    if(x == 0 && y ==0) //condition for changing to idle state
    {
        Sm.SetState(DUMMY_IDLE);
        return;
    }

    if(x!=0)
    {
        x == -1 ? Sm.SetFlip(Flip::N) : Sm.SetFlip(Flip::H);
    }
    Sm.Parent.Box += Vector2(x,y)*200*Dt;
}

