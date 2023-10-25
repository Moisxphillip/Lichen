#ifndef FOG_EVENTCHAIN
#define FOG_EVENTCHAIN

#include "Components/Component.hpp"
#include <list>
#include <functional>

class Event
{
    public:
        std::function<void()> Callback;
        std::function<bool()> RunCondition;
        std::function<bool()> ExitCondition;
        bool Loop;

        Event(std::function<void()> Callback, std::function<bool()> RunCondition = nullptr,
            std::function<bool()> ExitCondition = nullptr, bool Loop = false);
        void Run();
};

class EventChain : public Component
{
    private:
        std::list<Event> _Events;
        ComponentType _Activator;
        bool _TouchedActivator;
    
    public:
        EventChain(GameObject& Parent, ComponentType Activator = ComponentType::None);
        void PushEvent(Event New);
        void PopEvent();
        void Update(float Dt);
        void OnCollision(GameObject&);

};

#endif//FOG_EVENTCHAIN