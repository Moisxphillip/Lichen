#include "Enemy/Slime.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"

//Define names for the SMState enums, so it's easier to know which state you're using
#define SLIME_IDLE SMState::Type01
#define SLIME_WALK SMState::Type02

Slime::Slime(GameObject& Parent, std::string Label)
: StateMachine(Parent, Label)
{
    MyCollider = nullptr;
}

void Slime::SMStart()
{
    //Add the spritesheet(s) with all states and frames
    Sprite* slime = new Sprite(Parent, "./res/img/slime.png", 12, 6, 2, 0.2f);
    Parent.Depth = DepthMode::Dynamic;
    Parent.Box.Redimension(Vector2(slime->GetWidth(), slime->GetHeight()));
    AddSprite(slime);
    MyCollider = new AACircle(Parent, ColliderKind::Rigid, Circle(0,0,slime->GetWidth()/2));
    MyCollider->SetFriction(0.1f);
    MyCollider->GetBall().SetCenter(Parent.Box.Center());
    Parent.AddComponent(MyCollider);
    
    //Create an idle state
    StateInfo SI = {SLIME_IDLE, 0, 6, 0.2f, true, true}; //these are for setting up the spritesheet portion on update
    SlimeIdle* Slime = new SlimeIdle(SI);
    AddState(SLIME_IDLE, Slime);
    SetState(SLIME_IDLE);

    //Create a walk state
    SI = {SLIME_WALK, 6, 6, 0.2f, true, true};
    SlimeWalk* Dum = new SlimeWalk(SI);
    AddState(SLIME_WALK, Dum);
}

//------------------------------IDLE------------------------------
SlimeIdle::SlimeIdle(const StateInfo& Specs)
: GenericState(Specs)
{
}

void SlimeIdle::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Input& Ip = Input::Instance();
    if(Ip.MouseJustPressed(MouseButton::Right))
    {
        Slime* Dum = reinterpret_cast<Slime*>(&Sm);
        Dum->Target = Ip.MousePosition();
        Sm.SetState(SLIME_WALK);
        Dum->Target.x - Dum->Parent.Box.Center().x < 0 ? Sm.SetFlip(Flip::H) : Sm.SetFlip(Flip::N);
    }
}

//------------------------------WALK------------------------------
SlimeWalk::SlimeWalk(const StateInfo& Specs)
: GenericState(Specs)
{
}

void SlimeWalk::PhysicsUpdate(StateMachine& Sm, float Dt)
{
    Slime* Dum = reinterpret_cast<Slime*>(&Sm); //Cast to access child class information

    if(Dum->Parent.Box.Center() == Dum->Target || Input::Instance().MouseJustPressed(MouseButton::Left))
    {
        Sm.SetState(SLIME_IDLE);
        return;
    }

    Vector2 Move = Dum->Parent.Box.Center().MoveTo(Dum->Target, 250*Dt);
    Dum->MyCollider->SetVelocity(Move);

}

