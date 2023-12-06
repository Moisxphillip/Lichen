#ifndef GAME_CRITTER
#define GAME_CRITTER

#include "Components/StateMachine.hpp"
#include "Tools/Timer.hpp"
#include "Tools/Xrand.hpp"



//-------------------------------------------Bird----------------------------------------------
class Bird : public StateMachine
{
    private:

    public:
        Bird(GameObject& Parent, std::string Label = "Bird");
        ~Bird();
        void SMStart();
};

//-------------------------------------------States----------------------------------------------

//Idle
class BirdIdle : public GenericState
{
    private:
        Timer _ToPeckTimer;
        XrandF32 _Randomness;

    public:
        BirdIdle(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Fly
class BirdFly : public GenericState
{
    private:
        Vector2 _Direction;
        bool _Init;
    public:
        BirdFly(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};

//Peck
class BirdPeck : public GenericState
{
    private:
        Timer _PeckTimer;

    public:
        BirdPeck(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};



//-------------------------------------------Worm----------------------------------------------
class Worm : public StateMachine
{
    private:

    public:
        Worm(GameObject& Parent, std::string Label = "Worm");
        ~Worm();
        void SMStart();
};

//-------------------------------------------States----------------------------------------------

//Idle
class WormIdle : public GenericState
{
    private:

    public:
        WormIdle(const StateInfo& Specs);
        void Start();
        void Update(StateMachine& Sm, float Dt);
};

//Fly
class WormFlee : public GenericState
{
    private:
        Vector2 _Direction;
        bool _Init;
    public:
        WormFlee(const StateInfo& Specs);
        void Update(StateMachine& Sm, float Dt);
};



#endif//GAME_CRITTER