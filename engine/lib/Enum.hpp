#ifndef LYCHEN_ENUM
#define LYCHEN_ENUM
#include "SDL2/SDL_ttf.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <map>

//Game components must be defined by the game as they're named.
enum class ComponentType : long long int
{
    None =           0,
    Type01 =    1 << 0,
    Type02 =    1 << 1,
    Type03 =    1 << 2,
    Type04 =    1 << 3,
    Type05 =    1 << 4,
    Type06 =    1 << 5,
    Type07 =    1 << 6,
    Type08 =    1 << 7,
    Type09 =    1 << 8,
    Type10 =    1 << 9,
    Type11 =   1 << 10,
    Type12 =   1 << 11,
    Type13 =   1 << 12,
    Type14 =   1 << 13,
    Type15 =   1 << 14,
    Type16 =   1 << 15,
    Type17 =   1 << 16,
    Type18 =   1 << 17,
    Type19 =   1 << 18,
    Type20 =   1 << 19,
    Type21 =   1 << 20,
    Type22 =   1 << 21,
    Type23 =   1 << 22,
    Type24 =   1 << 23,
    Type25 =   1 << 24,
    Type26 =   1 << 25,
    Type27 =   1 << 26,
    Type28 =   1 << 27,
    Type29 =   1 << 28,
    Type30 =   1 << 29,
    Type31 =   1 << 30,
    Type32 = 1LL << 31,
    Type33 = 1LL << 32,
    Type34 = 1LL << 33,
    Type35 = 1LL << 34,
    Type36 = 1LL << 35,
    Type37 = 1LL << 36,
    Type38 = 1LL << 37,
    Type39 = 1LL << 38,
    Type40 = 1LL << 39,
    Type41 = 1LL << 40,
    Type42 = 1LL << 41,
    Type43 = 1LL << 42,
    Type44 = 1LL << 43,
    Type45 = 1LL << 44,
    Type46 = 1LL << 45,
    Type47 = 1LL << 46,
    Type48 = 1LL << 47,
    Type49 = 1LL << 48,
    Type50 = 1LL << 49,
    Type51 = 1LL << 50,
    Type52 = 1LL << 51,
    Type53 = 1LL << 52,
    Type54 = 1LL << 53,
    AACollider = 1LL << 54,
    Generic = 1LL << 55,
    Fade = 1LL << 56,
    Filter = 1LL << 57,
    CameraFollower = 1LL << 58,
    Collider = 1LL << 59,
    Sound = 1LL << 60,
    Sprite = 1LL << 61,
    Text = 1LL << 62,
    TileMap = 1LL << 63,
};

ComponentType operator|(ComponentType A, ComponentType B);

ComponentType operator&(ComponentType A, ComponentType B);

ComponentType operator^(ComponentType A, ComponentType B);

ComponentType operator~(ComponentType X);

enum class DepthMode
{
    Background,
    Dynamic, 
    Foreground,
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
enum class Key 
{
    Unknown,
    Space,
    Apostrophe,
    Comma,
    Minus,
    Period,
    Slash,
    Number0,
    Number1,
    Number2,
    Number3,
    Number4,
    Number5,
    Number6,
    Number7,
    Number8,
    Number9,
    Semicolon,
    Equal,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftBracket,
    Backslash,
    RightBracket,
    GraveAccent,
    World1,
    World2,
    Escape,
    Enter,
    Tab,
    Backspace,
    Insert,
    Delete,
    Right,
    Left,
    Down,
    Up,
    PageUp,
    PageDown,
    Home,
    End,
    CapsLock,
    ScrollLock,
    NumLock,
    PrintScreen,
    Pause,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    NumpadDecimal,
    NumpadDivide,
    NumpadMultiply,
    NumpadSubtract,
    NumpadAdd,
    NumpadEnter,
    NumpadEqual,
    LeftShift,
    LeftControl,
    LeftAlt,
    LeftSuper,
    RightShift,
    RightControl,
    RightAlt,
    RightSuper,
    Menu,
    LastKey
};

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

//Mask for optimizing collision interactions
enum class CollisionMask : unsigned long long int 
{
    None = 0,
    Type01 = 1 << 0,
    Type02 = 1 << 1,
    Type03 = 1 << 2,
    Type04 = 1 << 3,
    Type05 = 1 << 4,
    Type06 = 1 << 5,
    Type07 = 1 << 6,
    Type08 = 1 << 7,
    Type09 = 1 << 8,
    Type10 = 1 << 9,
    Type11 = 1 << 10,
    Type12 = 1 << 11,
    Type13 = 1 << 12,
    Type14 = 1 << 13,
    Type15 = 1 << 14,
    Type16 = 1 << 15,
    Type17 = 1 << 16,
    Type18 = 1 << 17,
    Type19 = 1 << 18,
    Type20 = 1 << 19,
    Type21 = 1 << 20,
    Type22 = 1 << 21,
    Type23 = 1 << 22,
    Type24 = 1 << 23,
    Type25 = 1 << 24,
    Type26 = 1 << 25,
    Type27 = 1 << 26,
    Type28 = 1 << 27,
    Type29 = 1 << 28,
    Type30 = 1 << 29,
    Type31 = 1 << 30,
    Type32 =1U << 31,
};

CollisionMask operator|(CollisionMask A, CollisionMask B);

CollisionMask operator&(CollisionMask A, CollisionMask B);

CollisionMask operator^(CollisionMask A, CollisionMask B);

CollisionMask operator~(CollisionMask X);

#endif//LYCHEN_ENUM