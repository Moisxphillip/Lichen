#include "UIController.hpp"
#include "Core/Input.hpp"

UIController::UIController(GameObject& Parent):Component(Parent),_UIFocused(false), _UIHidden(false){}

UIController::~UIController(){
    for (auto Component = rbegin(this->UIComponents); Component != rend(this->UIComponents); ++Component) 
        (*Component).reset();
    
    this->UIComponents.clear();
}

void UIController::Start(){}

void UIController::Update(float Dt){
    if(_UIHidden)
    {
        return;
    }

    Input InputController = Input::Instance();
    _UIFocused = false;
 
    for (auto Component = rbegin(UIComponents); Component != rend(UIComponents); ++Component){
        Vector2 MousePos = InputController.MousePosition();
        if((*Component)->IsInside(MousePos)){
             _UIFocused = true;
                (*Component)->Update(Dt, MousePos); 
                break;
        }
    }
}

void UIController::LateUpdate(float Dt){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
         if ((*Component)->ShouldBeClosed())
        {
             (*Component).reset();
        }
    }
}

void UIController::Render(){
    if(_UIHidden)
    {
        return;
    }

    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
        (*Component)->Render();
        break;
    }
}

void UIController::AddComponent(std::vector<std::string> Classes, UIComponent* Component){
    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    UIComponents.emplace_back(ComponentPointer);
}

bool UIController::IsUIHidden(){
    return _UIHidden;
}

bool UIController::IsUIFocused(){
    return _UIFocused;
}

void UIController::ShowUI(){
    _UIHidden = true;
}

void UIController::HideUI(){
    _UIHidden = false;
}

void UIController::ToggleHideUI(){
    _UIHidden = !_UIHidden;
}

