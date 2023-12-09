#include "UserInterface/UIComponent.hpp"
#include "Core/Input.hpp"
#include <algorithm>

UIComponent::UIComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position): 
    ParentComponent(ParentComponent),
    RelativePosition(Position), 
    IsActive(true), 
    UISprite(nullptr), 
    UIText(nullptr),
    WantsFocus(false) {}

UIComponent::UIComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes): 
    ParentComponent(ParentComponent),
    RelativePosition(Position), 
    IsActive(true), 
    UISprite(nullptr), 
    UIText(nullptr), 
    WantsFocus(false),
    Classes(Classes){}

UIComponent::~UIComponent()
{
   delete UISprite;
   delete UIText;
}

void UIComponent::Start(){}

void UIComponent::Update(Vector2 EventPos, float Dt)
{
    OnUpdate(EventPos, Dt);
}

void UIComponent::LateUpdate(Vector2 EventPos, float Dt)
{
    OnLateUpdate(EventPos, Dt);
}

void UIComponent::Trigger(Vector2 EventPos)
{
    Input InputController = Input::Instance();

    if(InputController.MouseJustPressed(MouseButton::Left))
    {
        if(InputController.MouseJustReleased(MouseButton::Left))
        {
            OnDoubleClick(EventPos);
        }
        else
        {
            OnClick(EventPos);
        }
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

void UIComponent::Render()
{
    if(!ParentComponent.expired())
    {
        AbsolutePosition = ParentComponent.lock()->AbsolutePosition + RelativePosition;
    } 
    else
    {
        AbsolutePosition = UIController::CurrentUI->Parent.Box.Position() + RelativePosition;
    }

    if(UISprite)
    {
        UISprite->Render(AbsolutePosition.x, AbsolutePosition.y);
    }
    if(UIText)
    {
        UIText->Render(Vector2(AbsolutePosition.x, AbsolutePosition.y));
    }

    ComplementaryRender();
}

void UIComponent::ComplementaryRender(){}

bool UIComponent::IsInside(Vector2 EventPos)
{
    if(!ParentComponent.expired())
    {
        AbsolutePosition = ParentComponent.lock()->AbsolutePosition + RelativePosition;
    } 
    else
    {
        AbsolutePosition = UIController::CurrentUI->Parent.Box.Position() + RelativePosition;
    }

    if(Rectangle(AbsolutePosition.x, AbsolutePosition.y, Width, Height).Contains(EventPos))
    {
        return true;
    }
    return false;
}

bool UIComponent::IsInside(Vector2 EventPos, float OffsetX, float OffsetY)
{
    if(!ParentComponent.expired())
    {
        AbsolutePosition = ParentComponent.lock()->AbsolutePosition + RelativePosition;
    } 
    else
    {
        AbsolutePosition = UIController::CurrentUI->Parent.Box.Position() + RelativePosition;
    }

    if(Rectangle(AbsolutePosition.x - OffsetX, AbsolutePosition.y - OffsetY, Width +OffsetX, Height + OffsetY).Contains(EventPos))
    {
        return true;
    }
    return false;
}

bool UIComponent::IsInside(Vector2 EventPos, float OffsetLeft, float OffsetRight, float OffsetTop, float OffsetBottom)
{
    if(!ParentComponent.expired())
    {
        AbsolutePosition = ParentComponent.lock()->AbsolutePosition + RelativePosition;
    } 
    else
    {
        AbsolutePosition = UIController::CurrentUI->Parent.Box.Position() + RelativePosition;
    }

    if(Rectangle(AbsolutePosition.x - OffsetLeft, AbsolutePosition.y - OffsetTop, Width +OffsetRight, Height + OffsetBottom).Contains(EventPos))
    {
        return true;
    }
    return false;
}


void UIComponent::LoadImage(std::string File)
{
    UISprite = new Sprite(UIController::CurrentUI->Parent, File);
    Width = UISprite->GetWidth();
    Height = UISprite->GetHeight();
}

void UIComponent::LoadImage(std::string File, int FrameCount, int Columns, int Rows)
{
    UISprite = new Sprite(UIController::CurrentUI->Parent, File, FrameCount, Columns, Rows);
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

void UIComponent::OnUpdate(Vector2 EventPos, float Dt){}

void UIComponent::OnLateUpdate(Vector2 EventPos, float Dt){}


// __________________________________________________________________UIGroupComponent _________________________________________________________________


UIGroupComponent::UIGroupComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position ):UIComponent(ParentComponent, Position){}

UIGroupComponent::UIGroupComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes):UIComponent(ParentComponent, Position, Classes){}

UIGroupComponent::~UIGroupComponent()
{
    for (auto Component = rbegin(this->_UIComponents); Component != rend(this->_UIComponents); ++Component) 
    {
        (*Component).reset();
    }
        

    this->_UIComponents.clear();
}

void UIGroupComponent::Start()
{
    GroupStart();

    for (auto Component: _UIComponents)
    {
        Component->Start();
    }
}

void UIGroupComponent::GroupStart(){}

void UIGroupComponent::Update(Vector2 EventPos, float Dt)
{
    OnUpdate(EventPos, Dt);
    
    for (auto Component : _UIComponents)
    {
        Component->Update(EventPos, Dt); 
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


void UIGroupComponent::LateUpdate(Vector2 EventPos, float Dt){
    OnLateUpdate(EventPos, Dt);

    for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
    {
        (*Component)->LateUpdate(EventPos, Dt);
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
    if(!ParentComponent.expired())
    {
        AbsolutePosition = ParentComponent.lock()->AbsolutePosition + RelativePosition;
    } 
    else
    {
        AbsolutePosition = UIController::CurrentUI->Parent.Box.Position() + RelativePosition;
    }

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

    UIComponent::ComplementaryRender();
}

void UIGroupComponent::AddComponent(UIComponent* Component){

    std::shared_ptr<UIComponent> ComponentPointer = std::shared_ptr<UIComponent>(Component);

    Component->Start();

    _UIComponents.emplace_back(ComponentPointer);
}

std::weak_ptr<UIComponent> UIGroupComponent::GetComponentAtPosition(Vector2 Position)
{
    if(IsInside(Position))
    {
        for (auto Component = begin(_UIComponents); Component != end(_UIComponents); ++Component)
        {
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

std::weak_ptr<UIComponent> UIGroupComponent::GetComponentByClass(std::string Class)
{
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






