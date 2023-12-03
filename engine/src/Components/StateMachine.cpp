#include "Components/StateMachine.hpp"
#include <algorithm>

StateMachine::StateMachine (GameObject& GameObjAssoc, const std::string& Label)
: Component(GameObjAssoc) 
{
    _Type = ComponentType::StateMachine;
    _CurrState = SMState::None;
    _Flip = Flip::N;
    _Label = Label;
}

StateMachine::~StateMachine()
{
    _Sections.clear();
}

void StateMachine::AddSprite(Sprite* Sheet) 
{
    if (Sheet == nullptr) 
    {
        Error("StateMachine::AddSprite: Sprite is null");
        return;
    }
    _Sections.emplace_back(std::unique_ptr<Sprite>(Sheet));
}

void StateMachine::AddState(SMState Id, GenericState* Add) 
{
    if(_States.count(Id))
    {
        Error("StateMachine::AddState: Tried to overwrite existing state");
        return;
    }
    _States.emplace(Id, std::unique_ptr<GenericState>(Add));
    // _States[Id] =  std::unique_ptr<GenericState>(Add);
}

void StateMachine::RemoveState(SMState Remove) 
{
     if(!_States.count(Remove))
    {
        Error("StateMachine::RemoveState: Tried to remove inexistent state");
        return;
    }
    _States.erase(Remove);
}

void StateMachine::SetState(SMState Set) 
{
    if(!_States.count(Set))
    {
        Error("StateMachine::SetState: Tried to set inexistent state");
        return;
    }
    StateInfo &X = _States[Set].get()->GetInfo();
    for(int i = 0; i< (int)_Sections.size();i++)
    {
        _Sections[i].get()->SetFrameSpan(X.FrameSpan);
        _Sections[i].get()->SetFrameStart(X.FrameStart);
        _Sections[i].get()->SetFrameTime(X.FrameTime);
        _Sections[i].get()->SetFrame(X.FrameStart);
        _Sections[i].get()->Loop = X.Loop;
    }
    _CurrState = Set;
    if(X.ResetOnStart)
    {
        _States[Set].get()->Start();
    }
}

void StateMachine::SetFlip(Flip Set)
{
    _Flip = Set;
}

Flip StateMachine::GetFlip()
{
    return _Flip;
}

bool StateMachine::HasState(SMState Compare) 
{
    return _States.count(Compare);
}

bool StateMachine::IsLabelled(std::string Compare) 
{
    return (_Label == Compare);
}

SMState StateMachine::GetCurrentState()
{
    return _CurrState;
}

void StateMachine::Start() 
{
    SMStart();
    if (_CurrState == SMState::None)
    {
        return;
    }
    _States[_CurrState].get()->Start();
}

void StateMachine::PhysicsUpdate(float Dt)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    SMState Now = _CurrState;
    _States[_CurrState].get()->PhysicsUpdate(*this, Dt);
    SMPhysicsUpdate(Dt);
    // if(Now != _CurrState)
    // {
    //     PhysicsUpdate(Dt);
    // }
}

void StateMachine::Update(float Dt)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    SMState Now = _CurrState;
    _States[_CurrState].get()->Update(*this, Dt);
    SMUpdate(Dt);
    for(int i = 0; i<(int)_Sections.size(); i++)
    {
        _Sections[i].get()->Update(Dt);
    }
    // if(Now != _CurrState)
    // {
    //     Update(Dt);
    // }
}

void StateMachine::LateUpdate(float Dt)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    SMState Now = _CurrState;
    _States[_CurrState].get()->LateUpdate(*this, Dt);
    SMLateUpdate(Dt);
    // if(Now != _CurrState)
    // {
    //     LateUpdate(Dt);
    // }
}

void StateMachine::Render()
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    for(int i = 0; i<(int)_Sections.size(); i++)
    {
        _Sections[i].get()->SetFlip(_Flip);
        _Sections[i].get()->Render();
    }
    _States[_CurrState].get()->Render(*this);
    SMRender();
}

void StateMachine::OnCollision(GameObject& Other)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    _States[_CurrState].get()->OnCollision(*this, Other);
    SMOnCollision(Other);
}

//Child Inheritance Interface Functions
void StateMachine::SMStart()
{
}

void StateMachine::SMPhysicsUpdate(float Dt)
{
}

void StateMachine::SMOnCollision(GameObject& Other)
{
}

void StateMachine::SMUpdate(float Dt)
{
}

void StateMachine::SMLateUpdate(float Dt)
{
}

void StateMachine::SMRender()
{
}

bool StateMachine::Is (ComponentType Type) 
{
    return static_cast<bool>(Type & this->_Type);
}


//_________________________________GenericState Interface__________________________________

GenericState::GenericState(const StateInfo& Specs)
{
    _Info = Specs;
}

StateInfo& GenericState::GetInfo()
{
    return _Info;
}

void GenericState::Start()
{
}

void GenericState::PhysicsUpdate(StateMachine& Sm, float Dt)
{
}

void GenericState::Update(StateMachine& Sm, float Dt)
{
}

void GenericState::LateUpdate(StateMachine& Sm, float Dt)
{
}

void GenericState::Render(StateMachine& Sm)
{
}

void GenericState::OnCollision(StateMachine& Sm, GameObject& Other)
{
}
