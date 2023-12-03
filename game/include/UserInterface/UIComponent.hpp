#ifndef LICHEN_UI_COMPONENT
#define LICHEN_UI_COMPONENT

#include "Components/Component.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include "UserInterface/UIController.hpp"

class UIController;

class UIComponent: public Component, public std::enable_shared_from_this<UIComponent>
{
protected:
    UIController& Controller;
    bool IsActive;

    virtual void OnHover(Vector2 EventPos);
    virtual void OnClick(Vector2 EventPos);
    virtual void OnRightClick(Vector2 EventPos);
    virtual void OnDoubleClick(Vector2 EventPos);
    virtual void OnHold(Vector2 EventPos);
    virtual void OnRelease(Vector2 EventPos);
    virtual void OnUpdate(Vector2 EventPos);    

public: 
    std::vector<std::string> Classes;
    Vector2 RelativePosition;
    Vector2 AbsolutePosition;
    Sprite* UISprite;
    Text* UIText;
    int Width;
    int Height;

    UIComponent(GameObject& Parent, UIController& Controller, Vector2 Position);
    UIComponent(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);

    ~UIComponent();
    
    bool HasClass(std::string Class);
    void AddClass(std::string Class);
    void RemoveClass(std::string Class);
    void LoadImage(std::string File);
    void LoadImage(std::string File, int FrameCount, int Columns, int Rows);

    virtual void Close();
    virtual bool ShouldBeClosed();
    virtual bool IsInside(Vector2 EventPos);
    virtual void Update(float Dt, Vector2 BasePos);
    virtual void Trigger(Vector2 EventPos);
    virtual void Render();
    virtual void Start();

    virtual std::weak_ptr<UIComponent> GetComponentAtPosition(Vector2 Position);
    virtual std::weak_ptr<UIComponent> GetComponentByClass(std::string Class) ;
};

class UIGroupComponent : public UIComponent
{
protected:
    std::vector<std::shared_ptr<UIComponent>> _UIComponents;
    
public: 
    UIGroupComponent(GameObject& Parent, UIController& Controller, Vector2 Position);
    UIGroupComponent(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    
    ~UIGroupComponent();

    virtual void Start();
    void Update(float Dt, Vector2 BasePos);
    virtual void Trigger(Vector2 EventPos);
    virtual void LateUpdate(float Dt);
    void Render();

    void AddComponent(UIComponent* Component);
    std::weak_ptr<UIComponent> GetComponentAtPosition(Vector2 Position) override;
    std::weak_ptr<UIComponent> GetComponentByClass(std::string Class) override;
};

#endif