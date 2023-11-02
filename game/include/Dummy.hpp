#ifndef LICHEN_DUMMY
#define LICHEN_DUMMY

#include "Components/StateMachine.hpp"
#include "Components/AACircle.hpp"

//The core entity
class Dummy : public StateMachine
{
    private:
        ~Dummy();

    public:
        AACircle* MyCollider;
        Dummy(GameObject& Parent, std::string Label = "Dummy");
        void SMStart();
        void OnCollision(GameObject& Other);

        static Dummy* Self;
};

//Idle state
class DummyIdle : public GenericState
{
    private:

    public:
    DummyIdle(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};

//Walk state
class DummyWalk : public GenericState
{
    private:

    public:
    DummyWalk(const StateInfo& Specs);
    void PhysicsUpdate(StateMachine& Sm, float Dt);
};
#endif//LICHEN_DUMMY