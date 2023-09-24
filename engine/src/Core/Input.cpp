#include <cmath>

#include "Core/Input.hpp"
#include "Core/Engine.hpp"
#include "Tools/Tools.hpp"

//Some petty optimization for not having a 400 key vector
std::map<int, Key> Input::_KeyCode = 
{
    {GLFW_KEY_UNKNOWN, Key::Unknown},
    {GLFW_KEY_SPACE, Key::Space},
    {GLFW_KEY_APOSTROPHE, Key::Apostrophe},
    {GLFW_KEY_COMMA, Key::Comma},
    {GLFW_KEY_MINUS, Key::Minus},
    {GLFW_KEY_PERIOD, Key::Period},
    {GLFW_KEY_SLASH, Key::Slash},
    {GLFW_KEY_0, Key::Number0},
    {GLFW_KEY_1, Key::Number1},
    {GLFW_KEY_2, Key::Number2},
    {GLFW_KEY_3, Key::Number3},
    {GLFW_KEY_4, Key::Number4},
    {GLFW_KEY_5, Key::Number5},
    {GLFW_KEY_6, Key::Number6},
    {GLFW_KEY_7, Key::Number7},
    {GLFW_KEY_8, Key::Number8},
    {GLFW_KEY_9, Key::Number9},
    {GLFW_KEY_SEMICOLON, Key::Semicolon},
    {GLFW_KEY_EQUAL, Key::Equal},
    {GLFW_KEY_A, Key::A},
    {GLFW_KEY_B, Key::B},
    {GLFW_KEY_C, Key::C},
    {GLFW_KEY_D, Key::D},
    {GLFW_KEY_E, Key::E},
    {GLFW_KEY_F, Key::F},
    {GLFW_KEY_G, Key::G},
    {GLFW_KEY_H, Key::H},
    {GLFW_KEY_I, Key::I},
    {GLFW_KEY_J, Key::J},
    {GLFW_KEY_K, Key::K},
    {GLFW_KEY_L, Key::L},
    {GLFW_KEY_M, Key::M},
    {GLFW_KEY_N, Key::N},
    {GLFW_KEY_O, Key::O},
    {GLFW_KEY_P, Key::P},
    {GLFW_KEY_Q, Key::Q},
    {GLFW_KEY_R, Key::R},
    {GLFW_KEY_S, Key::S},
    {GLFW_KEY_T, Key::T},
    {GLFW_KEY_U, Key::U},
    {GLFW_KEY_V, Key::V},
    {GLFW_KEY_W, Key::W},
    {GLFW_KEY_X, Key::X},
    {GLFW_KEY_Y, Key::Y},
    {GLFW_KEY_Z, Key::Z},
    {GLFW_KEY_LEFT_BRACKET, Key::LeftBracket},
    {GLFW_KEY_BACKSLASH, Key::Backslash},
    {GLFW_KEY_RIGHT_BRACKET, Key::RightBracket},
    {GLFW_KEY_GRAVE_ACCENT, Key::GraveAccent},
    {GLFW_KEY_WORLD_1, Key::World1},
    {GLFW_KEY_WORLD_2, Key::World2},
    {GLFW_KEY_ESCAPE, Key::Escape},
    {GLFW_KEY_ENTER, Key::Enter},
    {GLFW_KEY_TAB, Key::Tab},
    {GLFW_KEY_BACKSPACE, Key::Backspace},
    {GLFW_KEY_INSERT, Key::Insert},
    {GLFW_KEY_DELETE, Key::Delete},
    {GLFW_KEY_RIGHT, Key::Right},
    {GLFW_KEY_LEFT, Key::Left},
    {GLFW_KEY_DOWN, Key::Down},
    {GLFW_KEY_UP, Key::Up},
    {GLFW_KEY_PAGE_UP, Key::PageUp},
    {GLFW_KEY_PAGE_DOWN, Key::PageDown},
    {GLFW_KEY_HOME, Key::Home},
    {GLFW_KEY_END, Key::End},
    {GLFW_KEY_CAPS_LOCK, Key::CapsLock},
    {GLFW_KEY_SCROLL_LOCK, Key::ScrollLock},
    {GLFW_KEY_NUM_LOCK, Key::NumLock},
    {GLFW_KEY_PRINT_SCREEN, Key::PrintScreen},
    {GLFW_KEY_PAUSE, Key::Pause},
    {GLFW_KEY_F1, Key::F1},
    {GLFW_KEY_F2, Key::F2},
    {GLFW_KEY_F3, Key::F3},
    {GLFW_KEY_F4, Key::F4},
    {GLFW_KEY_F5, Key::F5},
    {GLFW_KEY_F6, Key::F6},
    {GLFW_KEY_F7, Key::F7},
    {GLFW_KEY_F8, Key::F8},
    {GLFW_KEY_F9, Key::F9},
    {GLFW_KEY_F10, Key::F10},
    {GLFW_KEY_F11, Key::F11},
    {GLFW_KEY_F12, Key::F12},
    {GLFW_KEY_F13, Key::F13},
    {GLFW_KEY_F14, Key::F14},
    {GLFW_KEY_F15, Key::F15},
    {GLFW_KEY_F16, Key::F16},
    {GLFW_KEY_F17, Key::F17},
    {GLFW_KEY_F18, Key::F18},
    {GLFW_KEY_F19, Key::F19},
    {GLFW_KEY_F20, Key::F20},
    {GLFW_KEY_F21, Key::F21},
    {GLFW_KEY_F22, Key::F22},
    {GLFW_KEY_F23, Key::F23},
    {GLFW_KEY_F24, Key::F24},
    {GLFW_KEY_F25, Key::F25},
    {GLFW_KEY_KP_0, Key::Numpad0},
    {GLFW_KEY_KP_1, Key::Numpad1},
    {GLFW_KEY_KP_2, Key::Numpad2},
    {GLFW_KEY_KP_3, Key::Numpad3},
    {GLFW_KEY_KP_4, Key::Numpad4},
    {GLFW_KEY_KP_5, Key::Numpad5},
    {GLFW_KEY_KP_6, Key::Numpad6},
    {GLFW_KEY_KP_7, Key::Numpad7},
    {GLFW_KEY_KP_8, Key::Numpad8},
    {GLFW_KEY_KP_9, Key::Numpad9},
    {GLFW_KEY_KP_DECIMAL, Key::NumpadDecimal},
    {GLFW_KEY_KP_DIVIDE, Key::NumpadDivide},
    {GLFW_KEY_KP_MULTIPLY, Key::NumpadMultiply},
    {GLFW_KEY_KP_SUBTRACT, Key::NumpadSubtract},
    {GLFW_KEY_KP_ADD, Key::NumpadAdd},
    {GLFW_KEY_KP_ENTER, Key::NumpadEnter},
    {GLFW_KEY_KP_EQUAL, Key::NumpadEqual},
    {GLFW_KEY_LEFT_SHIFT, Key::LeftShift},
    {GLFW_KEY_LEFT_CONTROL, Key::LeftControl},
    {GLFW_KEY_LEFT_ALT, Key::LeftAlt},
    {GLFW_KEY_LEFT_SUPER, Key::LeftSuper},
    {GLFW_KEY_RIGHT_SHIFT, Key::RightShift},
    {GLFW_KEY_RIGHT_CONTROL, Key::RightControl},
    {GLFW_KEY_RIGHT_ALT, Key::RightAlt},
    {GLFW_KEY_RIGHT_SUPER, Key::RightSuper},
    {GLFW_KEY_MENU, Key::Menu}
};

int Input::_Ctr = 0;
Input* Input::_InputM = nullptr;
GLFWwindow* Input::_Window = nullptr;
bool  Input::_Controller1On = false;
bool  Input::_QuitRequested = false;
bool  Input::_KeyState[static_cast<int>(Key::LastKey)] = {false};
int   Input::_PrevKeyState[static_cast<int>(Key::LastKey)] = {0};

bool   Input::_MouseState[static_cast<int>(MouseButton::LastButton)] = {false};
int    Input::_PrevMouseState[static_cast<int>(MouseButton::LastButton)] = {0};
double Input::_MouseX = 0.0;
double Input::_MouseY = 0.0;
MouseScroll Input::_ScrollDirection = MouseScroll::None;

bool  Input::_ControllerState[static_cast<int>(ControllerButton::LastButton)] = {false};
int   Input::_PrevControllerState[static_cast<int>(ControllerButton::LastButton)] = {0};
float Input::_ControllerAxis[static_cast<int>(ControllerAxis::LastAxis)] = {0.0f};
float Input::_ControllerDeadzone = 0.2f;


Input& Input::Instance()
{
    if(_InputM == nullptr) //Only creates a new Input if there's no other instance of the class currently running
    {
        _InputM = new Input();
    }
    return *_InputM;
}

Input::Input()
{
    if(_InputM != nullptr)//Report error if there is another instance working already
    {
        Error("Input::Input: Instance already exists");
        return;
    }
    else //Register pointer as current instance
    {
        _InputM = this;
    }

    this->_QuitRequested = false;
    Init(Engine::Instance().GetWindow().GetGLWindow());
}

void Input::Init(GLFWwindow* _Window) 
{
    Input::_Window = _Window;
    glfwSetKeyCallback(_Window, KeyCallback);
    glfwSetMouseButtonCallback(_Window, MouseButtonCallback);
    glfwSetCursorPosCallback(_Window, CursorPosCallback);
    glfwSetScrollCallback(_Window, ScrollCallback);
    glfwSetJoystickCallback(ControllerCallback);
    glfwSetFramebufferSizeCallback(_Window, WindowResizeCallback);

    glfwSetInputMode(_Window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(_Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    // Init controllers
    if (glfwJoystickPresent(GLFW_JOYSTICK_1)) 
    {
        _Controller1On = true;
    } 
    else 
    {
        _Controller1On = false;
    }
}

bool Input::QuitRequested() 
{
    return _QuitRequested;
}

void Input::Update()
{
    _Ctr++;
    glfwPollEvents();

    if(glfwWindowShouldClose(_Window))//Remember to use the window function when testing stuff without input class
    {
        _QuitRequested = true; 
    }

    // Update controller states
    if (_Controller1On) 
    {
        GLFWgamepadstate ControllerState;
        glfwGetGamepadState(GLFW_JOYSTICK_1, &ControllerState);
        for (int i = 0; i < static_cast<int>(ControllerAxis::LastAxis); ++i) 
        {
            _ControllerAxis[i] = ControllerState.axes[i];
        }
        for (int i = 0; i < static_cast<int>(ControllerButton::LastButton); ++i) 
        {
            if(_ControllerState[i] != ControllerState.buttons[i])
            {
                _PrevControllerState[i] = _Ctr;
            }
            _ControllerState[i] = ControllerState.buttons[i];
        }
    }

    //TODO move to appropriate place later.
    //TODO Store previous dimensions to restore size when window frame is back
    //TODO and maximize window when setting it to borderless 
    if(KeyJustPressed(Key::F11))
    {
        glfwSetWindowAttrib(_Window, GLFW_DECORATED, GLFW_FALSE);
    }
    
    if(KeyJustPressed(Key::F10))
    {
        glfwSetWindowAttrib(_Window, GLFW_DECORATED, GLFW_TRUE);
    }

}

// Key functions
bool Input::KeyJustPressed(Key KbKey) 
{
    return _KeyState[static_cast<int>(KbKey)] && _PrevKeyState[static_cast<int>(KbKey)] == _Ctr;
}

bool Input::KeyPressedDown(Key KbKey) 
{
    return _KeyState[static_cast<int>(KbKey)];
}

bool Input::KeyJustReleased(Key KbKey) 
{
    return !_KeyState[static_cast<int>(KbKey)] && _PrevKeyState[static_cast<int>(KbKey)] == _Ctr;
}

bool Input::KeyReleased(Key KbKey) 
{
    return !_KeyState[static_cast<int>(KbKey)];
}

// Mouse Button functions
bool Input::MouseJustPressed(MouseButton Button) 
{
    return _MouseState[static_cast<int>(Button)] && _PrevMouseState[static_cast<int>(Button)] == _Ctr;
}

bool Input::MousePressedDown(MouseButton Button)
{
    return _MouseState[static_cast<int>(Button)];
}

bool Input::MouseJustReleased(MouseButton Button)
{
    return !_MouseState[static_cast<int>(Button)] && _PrevMouseState[static_cast<int>(Button)] == _Ctr;
}

bool Input::MouseReleased(MouseButton Button)
{
    return !_MouseState[static_cast<int>(Button)];
}

Vector2 Input::MousePosition()
{
    Window& Win = Engine::Instance().GetWindow();

    return Vector2(
        (float)_MouseX * (float)Win.GetProjectionWidth()/(float)Win.GetWidth(),
        (float)_MouseY * (float)Win.GetProjectionHeight()/(float)Win.GetHeight())
        + Engine::Instance().CurrentScene().Cam.Position();
}

// Controller functions
bool Input::ControllerButtonJustPressed(ControllerButton Button) 
{
    return _ControllerState[static_cast<int>(Button)] && _PrevControllerState[static_cast<int>(Button)] == _Ctr;
}

bool Input::ControllerButtonPressedDown(ControllerButton Button) 
{
    return _ControllerState[static_cast<int>(Button)];
}

bool Input::ControllerButtonJustReleased(ControllerButton Button) 
{
    return !_ControllerState[static_cast<int>(Button)] && _PrevControllerState[static_cast<int>(Button)] == _Ctr;
}

bool Input::ControllerButtonReleased(ControllerButton Button) 
{
    return !_ControllerState[static_cast<int>(Button)];
}

float Input::GetControllerAxis(ControllerAxis Axis) 
{
    if (static_cast<int>(Axis) >= 0 
        && static_cast<int>(Axis) < static_cast<int>(ControllerAxis::LastAxis) 
        && abs(_ControllerAxis[static_cast<int>(Axis)]) > _ControllerDeadzone) 
    {
        return _ControllerAxis[static_cast<int>(Axis)];
    }
    return 0.0f;
}

void Input::SetControllerButtonDeadzone(float Deadzone) 
{
    _ControllerDeadzone = Deadzone;
}

void Input::VibrateController(float LeftMotor, float RightMotor) 
{
    if (_Controller1On) 
    {
        // Not supported yet by GLFW
    }
}

//Callbacks for events
void Input::KeyCallback(GLFWwindow* GLWindow, int KbKey, int Scancode, int Action, int Mods)
{
    if(!_KeyCode.count(KbKey))
    {
        return;
    }

    if (Action == GLFW_PRESS) 
    {
        _KeyState[static_cast<int>(_KeyCode[KbKey])] = true;
        _PrevKeyState[static_cast<int>(_KeyCode[KbKey])] = _Ctr;
    } 
    else if (Action == GLFW_RELEASE) 
    {
        _KeyState[static_cast<int>(_KeyCode[KbKey])] = false;
        _PrevKeyState[static_cast<int>(_KeyCode[KbKey])] = _Ctr;
    }
}

void Input::MouseButtonCallback(GLFWwindow* GLWindow, int Button, int Action, int Mods)
{
    if (Action == GLFW_PRESS) 
    {
        _MouseState[Button] = true;
        _PrevMouseState[Button] = _Ctr;
    } 
    else if (Action == GLFW_RELEASE) 
    {
        _MouseState[Button] = false;
        _PrevMouseState[Button] = _Ctr;
    }
}

void Input::CursorPosCallback(GLFWwindow* GLWindow, double XPos, double YPos) 
{
    _MouseX = XPos;
    _MouseY = YPos;
}

void Input::ScrollCallback(GLFWwindow* GLWindow, double XOffset, double YOffset) 
{
    if (YOffset > 0) 
    {
        _ScrollDirection = MouseScroll::Up;
        return;
    }
    else if (YOffset < 0)
    {
        _ScrollDirection = MouseScroll::Down;
        return;
    }
    _ScrollDirection = MouseScroll::None;
}

//TODO Add multi controller management
void Input::ControllerCallback(int ID, int Event) 
{
    if (ID == GLFW_JOYSTICK_1)
    {
        if (Event == GLFW_CONNECTED) 
        {
            _Controller1On = true;
        } 
        else if (Event == GLFW_DISCONNECTED) 
        {
            _Controller1On = false;
        }
    }
}

void Input::WindowResizeCallback(GLFWwindow* GLWindow , int W, int H)
{
    Window& Win = Engine::Instance().GetWindow();
    int x=0, y=0, w, h;
    glfwGetFramebufferSize(GLWindow, &w, &h);
    Win.SetWidth(w);
    Win.SetHeight(h);
    float DesiredRatio = (float)Win.GetProjectionWidth()/(float)Win.GetProjectionHeight();
    float AspectRatio = (float)w/(float)h;

    if(DesiredRatio < AspectRatio)
    {
        int nW = (int)(h * DesiredRatio);
        x = (w - nW)/2;
        y = 0;
        w = nW;
    }
    else if(DesiredRatio > AspectRatio)
    {
        int nH = (int)(w/DesiredRatio);
        x = 0;
        y = (h-nH)/2;
        h = nH;
    }
    glViewport(x,y,w,h);
}
