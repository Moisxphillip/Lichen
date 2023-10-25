#ifndef GAME_CONTROLS
#define GAME_CONTROLS

#include <map>
#include <vector>
#include <functional>
#include <Math/Vector2.hpp>

enum class GameControls
{
    Up,
    Down,
    Left,
    Right,
    
    Attack,
    Special,
    Dash,
};

enum class ControlCheck
{
    MouseButton,
    Key,
    ControllerButton,
};

class Controls
{
    private:
        static std::map<GameControls, std::vector< std::pair<ControlCheck, int> > > _Control;
    public:
        Controls();
        static bool IsPressed(GameControls Action);
        static bool IsJustPressed(GameControls Action);
        static bool IsReleased(GameControls Action);
        static bool IsJustReleased(GameControls Action);
        static Vector2 GetAxes();

};



#endif//GAME_CONTROLS