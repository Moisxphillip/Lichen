#ifndef GAME_ONDEL
#define GAME_ONDEL

#include "Components/Component.hpp"
#include <functional>

class OnDelete : public Component
{
    public:
    OnDelete(GameObject& Parent, std::function<void()> ToDo);
    ~OnDelete();
    std::function<void()> ToDo;
};

#endif// GAME_ONDEL