#ifndef LICHEN_UI_CONTROLLER
#define LICHEN_UI_CONTROLLER

#include "Components/Component.hpp"
#include <unordered_map>
#include "UserInterface/UIComponent.hpp"

class UIComponent;

class UIController : public Component {
private:
    bool _UIHidden;
    bool _UIFocused;
    std::vector<std::shared_ptr<UIComponent>> UIComponents;

public: 
    static UIController* CurrentUI;

    UIController(GameObject& Parent);
    ~UIController();

    virtual void Start();
    void Update(float Dt);
    void LateUpdate(float Dt);
    void Render();

    std::weak_ptr<UIComponent> AddComponent(UIComponent* Component);
    std::weak_ptr<UIComponent> GetComponentAtPosition(Vector2 Position);
    std::weak_ptr<UIComponent> GetComponentByClass(std::string Class);

    bool IsUIHidden();
    bool IsUIFocused();
    void ShowUI();
    void HideUI();
    void ToggleHideUI();
    Vector2 Position();
};

#endif