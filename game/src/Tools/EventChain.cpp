#include "Tools/EventChain.hpp"

//------------------------------EVENT------------------------------
Event::Event(std::function<void()> Callback, std::function<bool()> RunCondition, std::function<bool()> ExitCondition,  bool Loop)
: Callback(Callback), RunCondition(RunCondition), ExitCondition(ExitCondition), Loop(Loop)
{
}

void Event::Run() 
{
    if (Callback) 
    {
        Callback();
    }
}


//------------------------------EVENTCHAIN------------------------------
EventChain::EventChain(GameObject& Parent, ComponentType Activator)
: Component(Parent)
{
    _TouchedActivator = false;
    _Activator = Activator;
}

void EventChain::PushEvent(Event New)
{
    _Events.push_back(New);
}

void EventChain::PopEvent()
{
    if(_Events.empty())
    {
        return;
    }
    _Events.pop_front();
}

void EventChain::OnCollision(GameObject& Other)
{
    if(_Activator == ComponentType::None)
    {
        return;
    }
    _TouchedActivator = _TouchedActivator || Other.Contains(_Activator);
}

void EventChain::Update(float Dt)
{
    if (_Events.empty() || ((_Activator != ComponentType::None) && !_TouchedActivator))
    {
        return;
    }

    Event& CurrentEvent = _Events.front();

    if (CurrentEvent.RunCondition && !CurrentEvent.RunCondition() )
    {
        return;
    }

    CurrentEvent.Run();
    _TouchedActivator = false;

    if (CurrentEvent.ExitCondition && CurrentEvent.ExitCondition() || !CurrentEvent.Loop) 
    {
        PopEvent();
    }
}
