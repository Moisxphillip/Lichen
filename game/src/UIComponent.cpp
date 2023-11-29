#include "UIComponent.hpp"
#include "Core/Input.hpp"

UIComponent::UIComponent(): _IsActive(true), _UISprite(nullptr), _UIText(nullptr){}

UIComponent::~UIComponent(){
   delete _UISprite;
   delete _UIText;
}


void UIComponent::Start(){
}

void UIComponent::Update(float Dt, Vector2 EventPos){
    Input InputController = Input::Instance();

    OnUpdate(EventPos);

    if(InputController.MouseJustPressed(MouseButton::Left))
    {
        OnClick(EventPos);
    }
    else if( InputController.MouseJustPressed(MouseButton::Right))
    {
        OnRightClick(EventPos);
    }
    else if( InputController.MousePressedDown(MouseButton::Left))
    {
        OnHold(EventPos);
    }
    else if(InputController.MouseJustReleased(MouseButton::Left))
    {
        OnRelease(EventPos);
    }
    else 
    {
        OnHover(EventPos);
    }
}

void UIComponent::Render(){
    if(_UISprite)
    {
        _UISprite->Render();
    }
    if(_UIText)
    {
        _UIText->Render();
    }
}

bool UIComponent::IsInside(Vector2 Pos){
    if(Pos.x >= Position.x &&
        Pos.x < Position.x + Width &&
        Pos.y >= Position.y  &&
        Pos.y < Position.y + Height 
    )
    {
        return true;
    }
    return false;
}

void UIComponent::Close(){
    _IsActive = false;
}

bool UIComponent::ShouldBeClosed(){
    return _IsActive;
}


void UIComponent::OnHover(Vector2 EventPos){}

void UIComponent::OnClick(Vector2 EventPos){}

void UIComponent::OnRightClick(Vector2 EventPos){
}

void UIComponent::OnHold(Vector2 EventPos){}

void UIComponent::OnRelease(Vector2 EventPos){}

void UIComponent::OnUpdate(Vector2 EventPos){}

// __________________________________________________________________UIGroupComponent _________________________________________________________________


UIGroupComponent::UIGroupComponent(){}

UIGroupComponent::~UIGroupComponent(){
    for (auto Component = rbegin(this->_UIComponents); Component != rend(this->_UIComponents); ++Component) 
        (*Component).reset();
    
    this->_UIComponents.clear();
}

void UIGroupComponent::Start(){}

void UIGroupComponent::Update(float Dt, Vector2 EventPos){
    for (auto Component = rbegin(_UIComponents); Component != rend(_UIComponents); ++Component){
        if((*Component)->IsInside(EventPos)){
                (*Component)->Update(Dt, EventPos); 
                break;
        }
    }
}

void UIGroupComponent::LateUpdate(float Dt){
    for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component){
         if ((*Component)->ShouldBeClosed())
        {
             (*Component).reset();
        }
    }
}

void UIGroupComponent::Render(){
    for (auto Component: _UIComponents){
        Component->Render();
    }
}

void UIGroupComponent::AddComponent(UIComponent* Component){
    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    _UIComponents.emplace_back(ComponentPointer);
}

std::weak_ptr<UIComponent> UIGroupComponent::GetComponent(Vector2 Position){

}
