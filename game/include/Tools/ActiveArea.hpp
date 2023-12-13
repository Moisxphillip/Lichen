#ifndef GAME_ACTIVEAREA
#define GAME_ACTIVEAREA

#include <functional>
#include "Components/Component.hpp"

class ActiveArea : public Component
{
    private:
        bool _Active;
    public:
        ActiveArea(GameObject& Parent, Rectangle CoveredArea);
        std::function<void()> _OnActive;
        std::function<void()> _OnInactive;
        void SetOnActivation(std::function<void()> Activation);
        void SetOnInactivation(std::function<void()> Inactivation);
        void Update(float Dt);
};


#endif//GAME_ACTIVEAREA
