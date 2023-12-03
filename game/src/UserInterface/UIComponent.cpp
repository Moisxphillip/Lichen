#include "UserInterface/UIComponent.hpp"
#include "Core/Input.hpp"
#include <algorithm>

UIComponent::UIComponent(GameObject& Parent, UIController& Controller, Vector2 Position): 
    Component(Parent),
    Controller(Controller), 
    RelativePosition(Position), 
    IsActive(true), 
    UISprite(nullptr), 
    UIText(nullptr) 
    {
        AbsolutePosition = Position;
    }

UIComponent::UIComponent(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes): 
    Component(Parent),
    Controller(Controller), 
    RelativePosition(Position), 
    IsActive(true), 
    UISprite(nullptr), 
    UIText(nullptr), 
    Classes(Classes){}

UIComponent::~UIComponent()
{
   delete UISprite;
   delete UIText;
}

void UIComponent::Start()
{
    AbsolutePosition = RelativePosition;
}

void UIComponent::Update(float Dt, Vector2 BasePos)
{
    AbsolutePosition = BasePos + RelativePosition;
}

void UIComponent::Trigger(Vector2 EventPos)
{
    Input InputController = Input::Instance();

    if(InputController.MouseJustPressed(MouseButton::Left))
    {
        OnClick(EventPos);
    }
    else if( InputController.MouseJustPressed(MouseButton::Right))
    {
        if(InputController.MouseJustReleased(MouseButton::Right))
        {
            OnDoubleClick(EventPos);
        }
        else
        {
            OnRightClick(EventPos);
        }
        
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

void UIComponent::Render()
{
    if(UISprite)
    {
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
    }
    if(UIText)
    {
        UIText->Render();
    }
}

bool UIComponent::IsInside(Vector2 EventPos)
{

    if(EventPos.x >= AbsolutePosition.x &&
        EventPos.x < AbsolutePosition.x + Width &&
        EventPos.y >= AbsolutePosition.y  && 
        EventPos.y < AbsolutePosition.y + Height 
    )
    {
        return true;
    }
    return false;
}


void UIComponent::LoadImage(std::string File)
{
    UISprite = new Sprite(Parent, File);
    Width = UISprite->GetWidth();
    Height = UISprite->GetHeight();
}

void UIComponent::LoadImage(std::string File, int FrameCount, int Columns, int Rows)
{
    UISprite = new Sprite(Parent, File, FrameCount, Columns, Rows);
    Width = UISprite->GetWidth();
    Height = UISprite->GetHeight();
}

bool UIComponent::HasClass(std::string Class)
{
    if(std::find(Classes.begin(), Classes.end(), Class) == Classes.end()) 
    {
        return false;
    } 
    return true;
}

void UIComponent::AddClass(std::string Class)
{
    if(!HasClass(Class)) 
    {
        Classes.emplace_back(Class);
    } 
}

void UIComponent::RemoveClass(std::string Class)
{
    for (auto Cls = begin(Classes); Cls != end(Classes); ++Cls) {
        if((*Cls) == Class)
        {
            Classes.erase(Cls);
        }
    }
}

void UIComponent::Close()
{
    IsActive = false;
}

bool UIComponent::ShouldBeClosed()
{
    return !IsActive;
}

std::weak_ptr<UIComponent> UIComponent::GetComponentAtPosition(Vector2 Position)
{
    return weak_from_this();
}

std::weak_ptr<UIComponent> UIComponent::GetComponentByClass(std::string Class)
{
    if(std::find(Classes.begin(), Classes.end(), Class) == Classes.end())
    {
        return {};
    } 
    return weak_from_this();
}


void UIComponent::OnHover(Vector2 EventPos){}

void UIComponent::OnClick(Vector2 EventPos){}

void UIComponent::OnRightClick(Vector2 EventPos){}

void UIComponent::OnDoubleClick(Vector2 EventPos){}

void UIComponent::OnHold(Vector2 EventPos){}

void UIComponent::OnRelease(Vector2 EventPos){}

void UIComponent::OnUpdate(Vector2 EventPos){}



// __________________________________________________________________UIGroupComponent _________________________________________________________________


UIGroupComponent::UIGroupComponent(GameObject& Parent, UIController& Controller, Vector2 Position ):UIComponent(Parent, Controller, Position){}

UIGroupComponent::UIGroupComponent(GameObject& Parent,  UIController& Controller, Vector2 Position, std::vector<std::string> Classes):UIComponent(Parent, Controller, Position, Classes){}

UIGroupComponent::~UIGroupComponent(){
    for (auto Component = rbegin(this->_UIComponents); Component != rend(this->_UIComponents); ++Component) 
        (*Component).reset();
    
    this->_UIComponents.clear();
}

void UIGroupComponent::Start(){
    for (auto Component: _UIComponents){
        Component->Start();
    }
}

void UIGroupComponent::Update(float Dt, Vector2 BasePos){
    AbsolutePosition = BasePos + RelativePosition;

    for (auto Component : _UIComponents)
    {
        Component->Update(Dt, AbsolutePosition); 
    }
}

void UIGroupComponent::Trigger(Vector2 EventPos){
    for (auto Component = rbegin(_UIComponents); Component != rend(_UIComponents); ++Component)
    {
        if((*Component)->IsInside(EventPos))
        {
            (*Component)->Trigger(EventPos); 
            return;
        }
    }

    UIComponent::Trigger(EventPos);
}


void UIGroupComponent::LateUpdate(float Dt){
    for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
    {
        (*Component)->LateUpdate(Dt);
    }

    for(int i = 0; i< (int)(_UIComponents.size()); i++)
	{
		if(_UIComponents[i]->ShouldBeClosed())
		{
			_UIComponents.erase(_UIComponents.begin()+i); //Removes stuff discarded by RequestDelete()
			i--;
		}
	}
}

void UIGroupComponent::Render(){
    if(UISprite)
    {
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
    }
    if(UIText)
    {
        UIText->Render();
    }

    for (auto Component: _UIComponents)
    {
        Component->Render();
    }
}

void UIGroupComponent::AddComponent(UIComponent* Component){
    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    Component->Start();
    Component->AbsolutePosition = AbsolutePosition + Component->RelativePosition;

    _UIComponents.emplace_back(ComponentPointer);
}

std::weak_ptr<UIComponent> UIGroupComponent::GetComponentAtPosition(Vector2 Position){
    if(IsInside(Position))
    {
        for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component){
            std::weak_ptr<UIComponent> Cmpnt = (*Component)->GetComponentAtPosition(Position);
            if((*Component)->IsInside(Position))
            {
                return (*Component)->GetComponentAtPosition(Position);
            } 
        } 
        return weak_from_this();
    }
    return {};
}

std::weak_ptr<UIComponent> UIGroupComponent::GetComponentByClass(std::string Class){
    if((std::find(Classes.begin(), Classes.end(), Class) == Classes.end())) 
    {
        for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
        {
            std::weak_ptr<UIComponent> Cmpnt = (*Component)->GetComponentByClass(Class);
            if(!Cmpnt.expired())
            {
                return Cmpnt;
            } 
        }  
    } 
    else
    {
        return weak_from_this();
    }
    return {};
}






