#ifndef LICHEN_UI_BAG_MENU
#define LICHEN_UI_BAG_MENU

#include "UserInterface/UIComponent.hpp"
#include "Core/Camera.hpp"
#include "UserInterface/UIBasicComponents.hpp"

class UIBagButton : public UIComponent {
private:
    bool _IsOpened;
   
public:

    UIBagButton(GameObject& Parent, UIController& Controller, Vector2 Position);
    void Start();
    void OnRelease(Vector2 EventPos);
};

class UIBag : public UIGroupComponent {
public:
    static Vector2 LastBagRelativePosition;

    UIBag(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void Close();
    void OnRightClick(Vector2 EventPos);
    void LateUpdate(float Dt) override;
};

class UIBagClose : public UIComponent {
public:
    UIBagClose(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnClick(Vector2 EventPos);
};

class UIItenOptions: public UIGroupComponent {
public:
    UIItenOptions(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void Update(float Dt, Vector2 BasePos);
    bool IsInside(Vector2 EventPos);
};

class UIItenOptionUse: public UIComponent 
{
public:
    UIItenOptionUse(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnHover(Vector2 EventPos);
    void Update(float Dt, Vector2 BasePos);
};

class UIItenOptionThrow: public UIComponent {
public:
    UIItenOptionThrow(GameObject& Parent, UIController& Controller, Vector2 Position, std::vector<std::string> Classes);
    void Start();
    void OnHover(Vector2 EventPos);
    void Update(float Dt, Vector2 BasePos);
    
};


// class UIBagItens : public UIGroupComponent {};

// class UIBagItemSpace: public UIComponent {};

// class UIBagEquipmentSpace: public UIComponent {};


#endif