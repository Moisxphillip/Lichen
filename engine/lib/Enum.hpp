#ifndef LYCHEN_ENUM
#define LYCHEN_ENUM
#include "SDL2/SDL_ttf.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <map>

//Game components must be defined by the game as they're named.
enum class ComponentType : long long int
{
    _None =         0,
    _Type01 =  1 << 0,
    _Type02 =  1 << 1,
    _Type03 =  1 << 2,
    _Type04 =  1 << 3,
    _Type05 =  1 << 4,
    _Type06 =  1 << 5,
    _Type07 =  1 << 6,
    _Type08 =  1 << 7,
    _Type09 =  1 << 8,
    _Type10 =  1 << 9,
    _Type11 = 1 << 10,
    _Type12 = 1 << 11,
    _Type13 = 1 << 12,
    _Type14 = 1 << 13,
    _Type15 = 1 << 14,
    _Type16 = 1 << 15,
    _Type17 = 1 << 16,
    _Type18 = 1 << 17,
    _Type19 = 1 << 18,
    _Type20 = 1 << 19,
    _Type21 = 1 << 20,
    _Type22 = 1 << 21,
    _Type23 = 1 << 22,
    _Type24 = 1 << 23,
    _Type25 = 1 << 24,
    _Type26 = 1 << 25,
    _Type27 = 1 << 26,
    _Type28 = 1 << 27,
    _Type29 = 1 << 28,
    _Type30 = 1 << 29,
    _Type31 = 1 << 30,
    _Type32 = 1 << 31,
    //Extensible til' 64 if needed... I'm lazy to do that now.
    //TODO extend to 64 bits flags and add engine components with predefined values
};


enum class Flip
{
    N,
    H,
    V,
    HV,
};

typedef enum
{
    Stream  = 0x88E0,//GL_STREAM_DRAW
    Static  = 0x88E4,//GL_STATIC_DRAW
    Dynamic = 0x88E8 //GL_DYNAMIC_DRAW
} DrawMode;

enum class LoadTexture
{
    AsImage,
    AsText,
};

enum class TextStyle
{
    SOLID,
    SHADED,
    BLENDED
};

typedef enum 
{
    RIGHT = TTF_WRAPPED_ALIGN_RIGHT,
    CENTER = TTF_WRAPPED_ALIGN_CENTER,
    LEFT = TTF_WRAPPED_ALIGN_LEFT,
}TextAlignment;

// Key names
//Fix key mappings take a far larger vector than the actual keys represented. Maybe use a Map 
enum class Key 
{
    Unknown = GLFW_KEY_UNKNOWN,
    Space = GLFW_KEY_SPACE,
    Apostrophe = GLFW_KEY_APOSTROPHE,
    Comma = GLFW_KEY_COMMA,
    Minus = GLFW_KEY_MINUS,
    Period = GLFW_KEY_PERIOD,
    Slash = GLFW_KEY_SLASH,
    Number0 = GLFW_KEY_0,
    Number1 = GLFW_KEY_1,
    Number2 = GLFW_KEY_2,
    Number3 = GLFW_KEY_3,
    Number4 = GLFW_KEY_4,
    Number5 = GLFW_KEY_5,
    Number6 = GLFW_KEY_6,
    Number7 = GLFW_KEY_7,
    Number8 = GLFW_KEY_8,
    Number9 = GLFW_KEY_9,
    Semicolon = GLFW_KEY_SEMICOLON,
    Equal = GLFW_KEY_EQUAL,
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    LeftBracket = GLFW_KEY_LEFT_BRACKET,
    Backslash = GLFW_KEY_BACKSLASH,
    RightBracket = GLFW_KEY_RIGHT_BRACKET,
    GraveAccent = GLFW_KEY_GRAVE_ACCENT,
    World1 = GLFW_KEY_WORLD_1,
    World2 = GLFW_KEY_WORLD_2,
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
    Tab = GLFW_KEY_TAB,
    Backspace = GLFW_KEY_BACKSPACE,
    Insert = GLFW_KEY_INSERT,
    Delete = GLFW_KEY_DELETE,
    Right = GLFW_KEY_RIGHT,
    Left = GLFW_KEY_LEFT,
    Down = GLFW_KEY_DOWN,
    Up = GLFW_KEY_UP,
    PageUp = GLFW_KEY_PAGE_UP,
    PageDown = GLFW_KEY_PAGE_DOWN,
    Home = GLFW_KEY_HOME,
    End = GLFW_KEY_END,
    CapsLock = GLFW_KEY_CAPS_LOCK,
    ScrollLock = GLFW_KEY_SCROLL_LOCK,
    NumLock = GLFW_KEY_NUM_LOCK,
    PrintScreen = GLFW_KEY_PRINT_SCREEN,
    Pause = GLFW_KEY_PAUSE,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    F13 = GLFW_KEY_F13,
    F14 = GLFW_KEY_F14,
    F15 = GLFW_KEY_F15,
    F16 = GLFW_KEY_F16,
    F17 = GLFW_KEY_F17,
    F18 = GLFW_KEY_F18,
    F19 = GLFW_KEY_F19,
    F20 = GLFW_KEY_F20,
    F21 = GLFW_KEY_F21,
    F22 = GLFW_KEY_F22,
    F23 = GLFW_KEY_F23,
    F24 = GLFW_KEY_F24,
    F25 = GLFW_KEY_F25,
    Numpad0 = GLFW_KEY_KP_0,
    Numpad1 = GLFW_KEY_KP_1,
    Numpad2 = GLFW_KEY_KP_2,
    Numpad3 = GLFW_KEY_KP_3,
    Numpad4 = GLFW_KEY_KP_4,
    Numpad5 = GLFW_KEY_KP_5,
    Numpad6 = GLFW_KEY_KP_6,
    Numpad7 = GLFW_KEY_KP_7,
    Numpad8 = GLFW_KEY_KP_8,
    Numpad9 = GLFW_KEY_KP_9,
    NumpadDecimal = GLFW_KEY_KP_DECIMAL,
    NumpadDivide = GLFW_KEY_KP_DIVIDE,
    NumpadMultiply = GLFW_KEY_KP_MULTIPLY,
    NumpadSubtract = GLFW_KEY_KP_SUBTRACT,
    NumpadAdd = GLFW_KEY_KP_ADD,
    NumpadEnter = GLFW_KEY_KP_ENTER,
    NumpadEqual = GLFW_KEY_KP_EQUAL,
    LeftShift = GLFW_KEY_LEFT_SHIFT,
    LeftControl = GLFW_KEY_LEFT_CONTROL,
    LeftAlt = GLFW_KEY_LEFT_ALT,
    LeftSuper = GLFW_KEY_LEFT_SUPER,
    RightShift = GLFW_KEY_RIGHT_SHIFT,
    RightControl = GLFW_KEY_RIGHT_CONTROL,
    RightAlt = GLFW_KEY_RIGHT_ALT,
    RightSuper = GLFW_KEY_RIGHT_SUPER,
    Menu = GLFW_KEY_MENU,
    LastKey
};

/*
std::map<Key, int> KeyCode = {
    {Key::Unknown, GLFW_KEY_UNKNOWN},
    {Key::Space, GLFW_KEY_SPACE},
    {Key::Apostrophe, GLFW_KEY_APOSTROPHE},
    {Key::Comma, GLFW_KEY_COMMA},
    {Key::Minus, GLFW_KEY_MINUS},
    {Key::Period, GLFW_KEY_PERIOD},
    {Key::Slash, GLFW_KEY_SLASH},
    {Key::Number0, GLFW_KEY_0},
    {Key::Number1, GLFW_KEY_1},
    {Key::Number2, GLFW_KEY_2},
    {Key::Number3, GLFW_KEY_3},
    {Key::Number4, GLFW_KEY_4},
    {Key::Number5, GLFW_KEY_5},
    {Key::Number6, GLFW_KEY_6},
    {Key::Number7, GLFW_KEY_7},
    {Key::Number8, GLFW_KEY_8},
    {Key::Number9, GLFW_KEY_9},
    {Key::Semicolon, GLFW_KEY_SEMICOLON},
    {Key::Equal, GLFW_KEY_EQUAL},
    {Key::A, GLFW_KEY_A},
    {Key::B, GLFW_KEY_B},
    {Key::C, GLFW_KEY_C},
    {Key::D, GLFW_KEY_D},
    {Key::E, GLFW_KEY_E},
    {Key::F, GLFW_KEY_F},
    {Key::G, GLFW_KEY_G},
    {Key::H, GLFW_KEY_H},
    {Key::I, GLFW_KEY_I},
    {Key::J, GLFW_KEY_J},
    {Key::K, GLFW_KEY_K},
    {Key::L, GLFW_KEY_L},
    {Key::M, GLFW_KEY_M},
    {Key::N, GLFW_KEY_N},
    {Key::O, GLFW_KEY_O},
    {Key::P, GLFW_KEY_P},
    {Key::Q, GLFW_KEY_Q},
    {Key::R, GLFW_KEY_R},
    {Key::S, GLFW_KEY_S},
    {Key::T, GLFW_KEY_T},
    {Key::U, GLFW_KEY_U},
    {Key::V, GLFW_KEY_V},
    {Key::W, GLFW_KEY_W},
    {Key::X, GLFW_KEY_X},
    {Key::Y, GLFW_KEY_Y},
    {Key::Z, GLFW_KEY_Z},
    {Key::LeftBracket, GLFW_KEY_LEFT_BRACKET},
    {Key::Backslash, GLFW_KEY_BACKSLASH},
    {Key::RightBracket, GLFW_KEY_RIGHT_BRACKET},
    {Key::GraveAccent, GLFW_KEY_GRAVE_ACCENT},
    {Key::World1, GLFW_KEY_WORLD_1},
    {Key::World2, GLFW_KEY_WORLD_2},
    {Key::Escape, GLFW_KEY_ESCAPE},
    {Key::Enter, GLFW_KEY_ENTER},
    {Key::Tab, GLFW_KEY_TAB},
    {Key::Backspace, GLFW_KEY_BACKSPACE},
    {Key::Insert, GLFW_KEY_INSERT},
    {Key::Delete, GLFW_KEY_DELETE},
    {Key::Right, GLFW_KEY_RIGHT},
    {Key::Left, GLFW_KEY_LEFT},
    {Key::Down, GLFW_KEY_DOWN},
    {Key::Up, GLFW_KEY_UP},
    {Key::PageUp, GLFW_KEY_PAGE_UP},
    {Key::PageDown, GLFW_KEY_PAGE_DOWN},
    {Key::Home, GLFW_KEY_HOME},
    {Key::End, GLFW_KEY_END},
    {Key::CapsLock, GLFW_KEY_CAPS_LOCK},
    {Key::ScrollLock, GLFW_KEY_SCROLL_LOCK},
    {Key::NumLock, GLFW_KEY_NUM_LOCK},
    {Key::PrintScreen, GLFW_KEY_PRINT_SCREEN},
    {Key::Pause, GLFW_KEY_PAUSE},
    {Key::F1, GLFW_KEY_F1},
    {Key::F2, GLFW_KEY_F2},
    {Key::F3, GLFW_KEY_F3},
    {Key::F4, GLFW_KEY_F4},
    {Key::F5, GLFW_KEY_F5},
    {Key::F6, GLFW_KEY_F6},
    {Key::F7, GLFW_KEY_F7},
    {Key::F8, GLFW_KEY_F8},
    {Key::F9, GLFW_KEY_F9},
    {Key::F10, GLFW_KEY_F10},
    {Key::F11, GLFW_KEY_F11},
    {Key::F12, GLFW_KEY_F12},
    {Key::F13, GLFW_KEY_F13},
    {Key::F14, GLFW_KEY_F14},
    {Key::F15, GLFW_KEY_F15},
    {Key::F16, GLFW_KEY_F16},
    {Key::F17, GLFW_KEY_F17},
    {Key::F18, GLFW_KEY_F18},
    {Key::F19, GLFW_KEY_F19},
    {Key::F20, GLFW_KEY_F20},
    {Key::F21, GLFW_KEY_F21},
    {Key::F22, GLFW_KEY_F22},
    {Key::F23, GLFW_KEY_F23},
    {Key::F24, GLFW_KEY_F24},
    {Key::F25, GLFW_KEY_F25},
    {Key::Numpad0, GLFW_KEY_KP_0},
    {Key::Numpad1, GLFW_KEY_KP_1},
    {Key::Numpad2, GLFW_KEY_KP_2},
    {Key::Numpad3, GLFW_KEY_KP_3},
    {Key::Numpad4, GLFW_KEY_KP_4},
    {Key::Numpad5, GLFW_KEY_KP_5},
    {Key::Numpad6, GLFW_KEY_KP_6},
    {Key::Numpad7, GLFW_KEY_KP_7},
    {Key::Numpad8, GLFW_KEY_KP_8},
    {Key::Numpad9, GLFW_KEY_KP_9},
    {Key::NumpadDecimal, GLFW_KEY_KP_DECIMAL},
    {Key::NumpadDivide, GLFW_KEY_KP_DIVIDE},
    {Key::NumpadMultiply, GLFW_KEY_KP_MULTIPLY},
    {Key::NumpadSubtract, GLFW_KEY_KP_SUBTRACT},
    {Key::NumpadAdd, GLFW_KEY_KP_ADD},
    {Key::NumpadEnter, GLFW_KEY_KP_ENTER},
    {Key::NumpadEqual, GLFW_KEY_KP_EQUAL},
    {Key::LeftShift, GLFW_KEY_LEFT_SHIFT},
    {Key::LeftControl, GLFW_KEY_LEFT_CONTROL},
    {Key::LeftAlt, GLFW_KEY_LEFT_ALT},
    {Key::LeftSuper, GLFW_KEY_LEFT_SUPER},
    {Key::RightShift, GLFW_KEY_RIGHT_SHIFT},
    {Key::RightControl, GLFW_KEY_RIGHT_CONTROL},
    {Key::RightAlt, GLFW_KEY_RIGHT_ALT},
    {Key::RightSuper, GLFW_KEY_RIGHT_SUPER},
    {Key::Menu, GLFW_KEY_MENU},
    {Key::LastKey, -1}
};*/

// Mouse button names
enum class MouseButton 
{
    Left        = GLFW_MOUSE_BUTTON_1,
    Right       = GLFW_MOUSE_BUTTON_2,
    Middle      = GLFW_MOUSE_BUTTON_3,
    Button4     = GLFW_MOUSE_BUTTON_4,
    Button5     = GLFW_MOUSE_BUTTON_5,
    Button6     = GLFW_MOUSE_BUTTON_6,
    Button7     = GLFW_MOUSE_BUTTON_7,
    Button8     = GLFW_MOUSE_BUTTON_8,
    LastButton  = GLFW_MOUSE_BUTTON_LAST
};

enum class MouseScroll
{
    None,
    Up,
    Down,
};

enum class ControllerButton 
{
    A           = GLFW_GAMEPAD_BUTTON_A,
    B           = GLFW_GAMEPAD_BUTTON_B,
    X           = GLFW_GAMEPAD_BUTTON_X,
    Y           = GLFW_GAMEPAD_BUTTON_Y,
    LeftBumper  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    Back        = GLFW_GAMEPAD_BUTTON_BACK,
    Start       = GLFW_GAMEPAD_BUTTON_START,
    Guide       = GLFW_GAMEPAD_BUTTON_GUIDE,
    LeftThumb   = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    RightThumb  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    DPadUp      = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    DPadRight   = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    DPadDown    = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    DPadLeft    = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    LastButton
};

enum class ControllerAxis 
{
    LeftX = GLFW_GAMEPAD_AXIS_LEFT_X,
    LeftY = GLFW_GAMEPAD_AXIS_LEFT_Y,
    RightX = GLFW_GAMEPAD_AXIS_RIGHT_X,
    RightY = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    LeftTrigger = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    RightTrigger = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
    LastAxis
};



#endif//LYCHEN_ENUM