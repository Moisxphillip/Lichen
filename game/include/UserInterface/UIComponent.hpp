#ifndef LICHEN_UI_COMPONENT
#define LICHEN_UI_COMPONENT

#include "Components/Component.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include "UserInterface/UIController.hpp"

class UIController;

class UIComponent: public std::enable_shared_from_this<UIComponent>
{
protected:
    bool IsActive;

    virtual void OnHover(Vector2 EventPos);
    virtual void OnClick(Vector2 EventPos);
    virtual void OnRightClick(Vector2 EventPos);
    virtual void OnDoubleClick(Vector2 EventPos);
    virtual void OnHold(Vector2 EventPos);
    virtual void OnRelease(Vector2 EventPos);
    virtual void OnUpdate(Vector2 EventPos, float Dt);    
    virtual void OnLateUpdate(Vector2 EventPos, float DT);   

public: 
    std::vector<std::string> Classes;
    std::weak_ptr<UIComponent> ParentComponent;
    Vector2 RelativePosition;
    Vector2 AbsolutePosition;
    Sprite* UISprite;
    Text* UIText;
    int Width;
    int Height;

    UIComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);
    UIComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);

    ~UIComponent();

    virtual void Start();
    virtual void Render();
    virtual void Close();

    virtual void Update(Vector2 EventPos, float Dt);
    virtual void LateUpdate(Vector2 EventPos, float Dt);
    virtual void Trigger(Vector2 EventPos);
    

    bool ShouldBeClosed();
    bool HasClass(std::string Class);
    void AddClass(std::string Class);
    void RemoveClass(std::string Class);
    void LoadImage(std::string File);
    void LoadImage(std::string File, int FrameCount, int Columns, int Rows);

    bool IsInside(Vector2 EventPos);
    bool IsInside(Vector2 EventPos, float OffsetX, float OffsetY);
    bool IsInside(Vector2 EventPos, float OffsetLeft, float OffsetRight, float OffsetTop, float OffsetBottom);
    
    virtual std::weak_ptr<UIComponent> GetComponentAtPosition(Vector2 Position);
    virtual std::weak_ptr<UIComponent> GetComponentByClass(std::string Class) ;
};

class UIGroupComponent : public UIComponent
{
protected:
    std::vector<std::shared_ptr<UIComponent>> _UIComponents;
    
public: 
    UIGroupComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position);
    UIGroupComponent(std::weak_ptr<UIComponent> ParentComponent, Vector2 Position, std::vector<std::string> Classes);
    
    ~UIGroupComponent();

    void Start();
    void Render();

    void Trigger(Vector2 EventPos);
    void Update(Vector2 BasePos, float Dt);
    void LateUpdate( Vector2 BasePos, float Dt);

    virtual void GroupStart();

    void AddComponent(UIComponent* Component);
    std::weak_ptr<UIComponent> GetComponentAtPosition(Vector2 Position) override;
    std::weak_ptr<UIComponent> GetComponentByClass(std::string Class) override;
};

#endif