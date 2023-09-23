#ifndef LICHEN_STATEMACHINE
#define LICHEN_STATEMACHINE

#include "Component.hpp"    
#include "Sprite.hpp"
#include "Enum.hpp"
#include <map>

struct StateInfo
{
    SMState ThisState; //Enum for self-id
    int FrameStart, FrameSpan; //for setting correct frame span on sprite
    float FrameTime; 
    bool Loop; 
    bool ResetOnStart; //Calls the Start on a state switch, to reset values and behavior if desired
};

class GenericState;

class StateMachine: public Component
{
    protected:
        SMState _CurrState;
        std::vector<std::unique_ptr<Sprite>> _Sections; //For having body parts separated, but composing a full body at the end
        std::map<SMState, std::unique_ptr<GenericState>> _States;
        Flip _Flip;
        Vector2 _LastDirection;
        std::string _Label;

    public:
        StateMachine(GameObject& GameObjAssoc, const std::string& Label);
        ~StateMachine();
        void AddSprite(Sprite* Sheet);
        void AddState(SMState Id, GenericState* Add);
        void RemoveState(SMState Remove);
        void SetState(SMState Set);
        bool HasState(SMState Compare);
        bool IsLabelled(std::string Compare);
        SMState GetCurrentState();

        // Inheritance
        //These functions overwrite the StateMachine behavior, so use them only
        //if you intend to customize the final behavior.
        virtual void Start();
        virtual void PhysicsUpdate(float Dt);
        virtual void Update(float Dt);
        virtual void LateUpdate(float Dt);
        virtual void Render();
        virtual void OnCollision(GameObject& Other);
        virtual bool Is(ComponentType Type);

        //Use these function bodies to describe your entity custom actions while
        //preserving the StateMachine core management
        virtual void SMStart();
        virtual void SMPhysicsUpdate(float Dt);
        virtual void SMUpdate(float Dt);
        virtual void SMLateUpdate(float Dt);
        virtual void SMRender();


};

class GenericState
{
    private:
        StateInfo _Info;
    public:
        GenericState(const StateInfo& Specs);
        StateInfo& GetInfo();

        //Overwrite these to the desired behavior of that state
        virtual void Start();
        virtual void PhysicsUpdate(StateMachine& Sm, float Dt);
        virtual void Update(StateMachine& Sm, float Dt);
        virtual void LateUpdate(StateMachine& Sm, float Dt);
        virtual void Render(StateMachine& Sm);
        virtual void OnCollision(StateMachine& Sm, GameObject& Other);

};

#endif//LICHEN_STATEMACHINE