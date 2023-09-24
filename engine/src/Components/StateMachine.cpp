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
        _Sections[i].get()->SetFrameStart(X.FrameStart);
        _Sections[i].get()->SetFrameSpan(X.FrameSpan);
        _Sections[i].get()->SetFrameTime(X.FrameTime);
        _Sections[i].get()->Loop = X.Loop;
    }
    _CurrState = Set;
    if(X.ResetOnStart)
    {
        _States[Set].get()->Start();
    }
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
    _States[_CurrState].get()->PhysicsUpdate(*this, Dt);
    SMPhysicsUpdate(Dt);
}

void StateMachine::Update(float Dt)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    SMUpdate(Dt);
    _States[_CurrState].get()->Update(*this, Dt);
    for(int i = 0; i<(int)_Sections.size(); i++)
    {
        _Sections[i].get()->Update(Dt);
    }
}

void StateMachine::LateUpdate(float Dt)
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    _States[_CurrState].get()->LateUpdate(*this, Dt);
    SMLateUpdate(Dt);
}

void StateMachine::Render()
{
    if (_CurrState == SMState::None)
    {
        return;
    }
    for(int i = 0; i<(int)_Sections.size(); i++)
    {
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
}

//Child Inheritance Interface Functions
void StateMachine::SMStart()
{
}

void StateMachine::SMPhysicsUpdate(float Dt)
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



    // _SMStates.push_back(Add);
    // std::sort(_SMStates.begin(), _SMStates.end(),
    //     [](const StateInfo& A, const StateInfo& B)
    //     {
    //         return A.ThisState < B.ThisState;
    //     });

    // for(int i = 0; i< (int)_SMStates.size();i++)
    // {
    //     if(_SMStates[i].ThisState == Remove)
    //     {
    //         _SMStates.erase(_SMStates.begin()+i);
    //         return;
    //     }
    // }
    // Error("StateMachine::RemoveState: Attempted to delete inexistent state");

    // for(int i = 0; i< (int)_SMStates.size();i++)
    // {
    //     if(_SMStates[i].ThisState == Set)
    //     {
    //         X = _SMStates[i];
    //     }
    // }
    
    // sprites.resize(SMState::_statesCount);
    // for(int i=0; i < SMState::_statesCount; i++)
    //     sprites[i] = nullptr;
    // Sprite* spriteState = sprites[state].get();
    // spriteState->textureFlip = textureFlip;
    // spriteState->Render();
    // if(sprites[state] == nullptr) {
    //     SDL_Log("StateMachine::RemoveSMState: SMState");
    //     return;
    // } sprites[state].reset();
// void StateMachine::FlipSprite (Sprite::Axis axis) 
// {
//     SDL_RendererFlip flip = (axis == Sprite::HORIZONTAL) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_VERTICAL;
//     textureFlip = SDL_RendererFlip(textureFlip ^ flip);
// }
// bool StateMachine::SpriteIsFlipped () {
//     return ((textureFlip & SDL_FLIP_HORIZONTAL)? true : false);
// }
    // if (state != previousState)
    //     sprites[state].get()->SetFrame(0);
    // int directionX = (textureFlip ^ SDL_FLIP_HORIZONTAL)? 0 : 1;
    // int directionY = (textureFlip ^ SDL_FLIP_VERTICAL)? 0 : 1;
    // Collider* collider = (Collider*)associated.GetComponent(ComponentType::_Collider);
    // if (collider != nullptr) {
    //     if (directionX != lastDirection.x) {
    //         collider->offset.x = -collider->offset.x;
    //         associated.box.x -= collider->offset.x * 2.0f;
    //         lastDirection.x = directionX;
    //     }
    //     if (directionY != lastDirection.y) {
    //         collider->offset.y = -collider->offset.y;
    //         associated.box.y -= collider->offset.y * 2.0f;
    //         lastDirection.y = directionY;
    //     }
    // }
    // // melius colliders' pixel correction
    // associated.pixelColliderFix0 = lastDirection.x;