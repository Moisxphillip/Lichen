#include "Dummy.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"
#include "Mechanics/Combat.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define DUMMY_IDLE SMState::Type01
#define DUMMY_WALK SMState::Type02

Dummy* Dummy::Self;

Dummy::Dummy(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
    Self = this;
}

Dummy::~Dummy(){
    Self = nullptr;
}

void Dummy::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* galo = new Sprite(Parent, "./res/galor.png");
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(galo->GetWidth(), galo->GetHeight()));
    AddSprite(galo);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,galo->GetWidth()/6));
    MyCollider->SetFriction(0.1f);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
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


// #include <iostream>
// Stats Def{50, 50, 1, 0, 15, 0, 0, 0};
void Dummy::OnCollision(GameObject& Other)
{
    //Leftovers from combat tests. Far from ideal implementation, but gives an idea on how it should work
    // Stats Atk{50, 50, 1, 0, 0, 25, 25, 0};
    // AttackData Dta{5, (ScalingStats)(ScalingStats::Strength | ScalingStats::Dexterity)};
    // std::cout << Def << '\n';
    // int x =  Combat::Calculate(Atk, Dta, Def);
    // std::cout <<"This round damage: " << x << "\n\n";
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

    // Sm.Parent.Box += Vector2(x,y)*200*Dt;//For moving things that haven't a collider

    Dummy* Dum = reinterpret_cast<Dummy*>(&Sm); //Cast to access child class information
    // Dum->MyCollider->SetVelocity(Vector2(x,y).Normalized()*200*Dt); //Works but it's way more prone to bugs and glitches

    Dum->MyCollider->ApplyForce(Vector2(x,y).Normalized()*2000); //The best way to move stuff with a collider
}

