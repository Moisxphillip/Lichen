#include "UserInterface/UIController.hpp"
#include "UserInterface/UIBagMenu.hpp"
#include "UserInterface/UIPlayerBar.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"

UIController::UIController(GameObject& Parent):Component(Parent),_UIFocused(false), _UIHidden(false){}

UIController::~UIController(){
    for (auto Component = rbegin(this->UIComponents); Component != rend(this->UIComponents); ++Component) 
        (*Component).reset();
    
    this->UIComponents.clear();
}

void UIController::Start(){
    AddComponent(new UIBagButton(Parent, *this, Vector2(1180,630)));
    AddComponent(new UIPlayerBar(Parent, *this, Vector2(40,40)));
}

void UIController::Update(float Dt){
    Parent.Box.SetPosition(Camera::Position());

    if(_UIHidden)
    {
        return;
    }

    Input InputController = Input::Instance();
    _UIFocused = false;

    for(auto Component : UIComponents)
    {
        Component->Update(Dt, Parent.Box.Position());
    }
 
    for (auto Component = rbegin(UIComponents); Component != rend(UIComponents); ++Component){
        Vector2 MousePos = InputController.MousePosition();
        if((*Component)->IsInside(MousePos)){
             _UIFocused = true;
            (*Component)->Trigger(MousePos); 
            break;
        }
    }
}

void UIController::LateUpdate(float Dt){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
        (*Component)->LateUpdate(Dt);
    }

    for(int i = 0; i< (int)(UIComponents.size()); i++)
	{
		if(UIComponents[i]->ShouldBeClosed())
		{
			UIComponents.erase(UIComponents.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void UIController::Render(){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
        (*Component)->Render();
    }
}

std::weak_ptr<UIComponent> UIController::AddComponent(UIComponent* Component){
    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    UIComponents.emplace_back(ComponentPointer);

    (*ComponentPointer).Start();
    ComponentPointer->AbsolutePosition = Camera::Position() + ComponentPointer->RelativePosition;

    return std::weak_ptr<UIComponent>(ComponentPointer);
}

std::weak_ptr<UIComponent> UIController::GetComponentByClass(std::string Class){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component)
    {
        std::weak_ptr<UIComponent> Cmpnt = (*Component)->GetComponentByClass(Class);
        if(!Cmpnt.expired())
        {
            return Cmpnt;
        }
    }
    return {};
}

std::weak_ptr<UIComponent> UIController::GetComponentAtPosition(Vector2 Position){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component)
    {
        std::weak_ptr<UIComponent> Cmpnt = (*Component)->GetComponentAtPosition(Position);
        if(!Cmpnt.expired())
        {
            return Cmpnt;
        }  
    }
    return {};
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

