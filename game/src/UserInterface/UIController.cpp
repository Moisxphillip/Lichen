#include "UserInterface/UIController.hpp"
#include "UserInterface/UIRightBar.hpp"
#include "UserInterface/UIPlayerBar.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"

UIController* UIController::CurrentUI = nullptr;

bool UIController::_UIHidden = false;
bool UIController::_UIFocused = false;

UIController::UIController(GameObject& Parent):Component(Parent)
{
    CurrentUI = this;
}

UIController::~UIController(){
    for (auto Component = rbegin(this->UIComponents); Component != rend(this->UIComponents); ++Component) 
        (*Component).reset();
    
    this->UIComponents.clear();

    CurrentUI = nullptr;
}

void UIController::Start(){
    AddComponent(new UIRightBar({}, Vector2(1000,620)));
    AddComponent(new UIPlayerBar({}, Vector2(0,0)));
}

void UIController::Update(float Dt){
    _UIFocused = false;

    if(_UIHidden)
    {
        return;
    }

    Vector2 MousePos = Input::Instance().MousePosition();

    for(auto Component : UIComponents)
    {
        Component->Update(MousePos, Dt);
    }
 
    for (auto Component = rbegin(UIComponents); Component != rend(UIComponents); ++Component)
    {
        if((*Component)->IsInside(MousePos))
        {
            _UIFocused = true;
            (*Component)->Trigger(MousePos); 
            break;
        }
    }
}

void UIController::LateUpdate(float Dt)
{
    Vector2 MousePos = Input::Instance().MousePosition();

    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
        (*Component)->LateUpdate(MousePos, Dt);
    }

    for(int i = 0; i< (int)(UIComponents.size()); i++)
	{
		if(UIComponents[i]->ShouldBeClosed())
		{
			UIComponents.erase(UIComponents.begin()+i); 
			i--;
		}
	}
}

void UIController::Render(){
    for (auto Component = begin(UIComponents); Component != end(UIComponents); ++Component){
        (*Component)->Render();
    }
}

std::weak_ptr<UIComponent> UIController::AddComponent(UIComponent* Component)
{
    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    UIComponents.emplace_back(ComponentPointer);

    (*ComponentPointer).Start();

    return std::weak_ptr<UIComponent>(ComponentPointer);
}

std::weak_ptr<UIComponent> UIController::GetComponentByClass(std::string Class)
{
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

std::weak_ptr<UIComponent> UIController::GetComponentAtPosition(Vector2 Position)
{
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

Vector2 UIController::Position()
{
    return Parent.Box.Position();
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

