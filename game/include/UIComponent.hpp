#ifndef LICHEN_UI_COMPONENT
#define LICHEN_UI_COMPONENT

#include "Components/Component.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"

class UIComponent{
    

private:
    bool _IsActive;
    Sprite* _UISprite;
    Text* _UIText;

    virtual void OnHover(Vector2 EventPos);
    virtual void OnClick(Vector2 EventPos);
    virtual void OnRightClick(Vector2 EventPos);
    virtual void OnHold(Vector2 EventPos);
    virtual void OnRelease(Vector2 EventPos);
    virtual void OnUpdate(Vector2 EventPos);

public: 
    std::vector<std::string> Classes;
    Vector2 Position;
    int Width;
    int Height;

    UIComponent();
    ~UIComponent();

    void Update(float Dt, Vector2 EventPos);
    void Render();
    virtual void Start();
    bool IsInside(Vector2 Pos);

    void Close();
    bool ShouldBeClosed();
};

class UIGroupComponent : public UIComponent{
private:
    std::vector<std::shared_ptr<UIComponent>> _UIComponents;
    
public: 
    UIGroupComponent();
    ~UIGroupComponent();

    virtual void Start();
    void Update(float Dt, Vector2 EventPos);
    void LateUpdate(float Dt);
    void Render();

    void AddComponent(UIComponent* Component);
    std::weak_ptr<UIComponent> GetComponent(Vector2 Position);
};

#endif