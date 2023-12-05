#ifndef GAME_DISTTRIGGER
#define GAME_DISTTRIGGER

#include <functional>
#include "Components/Component.hpp"

enum class DistTriggerMode
{
    Disable,
    Delete,
    Custom,
};

class DistanceTrigger : public Component
{
    private:
        Component* _Subject;
        bool _Active;
        DistTriggerMode _Mode;
        float _MaxDistance;
        bool _OnBounds();
        std::function<void()> _OnActive;
        std::function<void()> _OnInactive;

    public:
        DistanceTrigger(GameObject& Parent, Component* Subject, float MaxDistance, DistTriggerMode Mode = DistTriggerMode::Disable);
        void SetOnActivation(std::function<void()> Activation);
        void SetOnInactivation(std::function<void()> Inactivation);
        void Update(float Dt);
};


#endif//GAME_DISTTRIGGER