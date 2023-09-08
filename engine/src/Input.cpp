#include <cmath>

#include "../lib/Input.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Tools.hpp"

// //Set value for singleton class
Input* Input::_InputM = nullptr;
GLFWwindow* Input::_Window = nullptr;
bool  Input::_Controller1On = false;
bool  Input::_QuitRequested = false;

bool  Input::_KeyState[static_cast<int>(Key::LastKey)] = {false};
bool  Input::_PrevKeyState[static_cast<int>(Key::LastKey)] = {false};

bool  Input::_MouseState[static_cast<int>(MouseButton::LastButton)] = {false};
bool  Input::_PrevMouseState[static_cast<int>(MouseButton::LastButton)] = {false};

bool  Input::_ControllerState[static_cast<int>(ControllerButton::LastButton)] = {false};
bool  Input::_PrevControllerState[static_cast<int>(ControllerButton::LastButton)] = {false};
float Input::_ControllerAxis[static_cast<int>(ControllerAxis::LastAxis)] = {0.0f};
float Input::_ControllerDeadzone = 0.2f;
double Input::_MouseX = 0.0;
double Input::_MouseY = 0.0;
MouseScroll Input::_ScrollDirection = MouseScroll::None;

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
    // Update previous Key and mouse Button states
    for (int i = 0; i < static_cast<int>(Key::LastKey); ++i)
    {
        _PrevKeyState[i] = _KeyState[i];
    }
    for (int i = 0; i < static_cast<int>(MouseButton::LastButton); ++i)
    {
        _PrevMouseState[i] = _MouseState[i];
    }

    if(Engine::Instance().GetWindow().QuitRequested())//Poll events is inside here, for tests with window alone
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
            _PrevControllerState[i] = _ControllerState[i];
            _ControllerState[i] = ControllerState.buttons[i];
        }
    }
}

// Key functions
bool Input::KeyJustPressed(Key KbKey) 
{
    return _KeyState[static_cast<int>(KbKey)] && !_PrevKeyState[static_cast<int>(KbKey)];
}

bool Input::KeyPressedDown(Key KbKey) 
{
    return _KeyState[static_cast<int>(KbKey)];
}

bool Input::KeyJustReleased(Key KbKey) 
{
    return !_KeyState[static_cast<int>(KbKey)] && _PrevKeyState[static_cast<int>(KbKey)];
}

bool Input::KeyReleased(Key KbKey) 
{
    return !_KeyState[static_cast<int>(KbKey)];
}

// Mouse Button functions
bool Input::MouseJustPressed(MouseButton Button) 
{
    return _MouseState[static_cast<int>(Button)] && !_PrevMouseState[static_cast<int>(Button)];
}

bool Input::MousePressedDown(MouseButton Button)
{
    return _MouseState[static_cast<int>(Button)];
}

bool Input::MouseJustReleased(MouseButton Button)
{
    return !_MouseState[static_cast<int>(Button)] && _PrevMouseState[static_cast<int>(Button)];
}

bool Input::MouseReleased(MouseButton Button)
{
    return !_MouseState[static_cast<int>(Button)];
}

Vector2 Input::MousePosition()
{
    return Vector2((float)_MouseX, (float)_MouseY) + Engine::Instance().CurrentState().Cam.Position();
}

// Controller functions
bool Input::ControllerButtonJustPressed(ControllerButton Button) 
{
    return _ControllerState[static_cast<int>(Button)] && !_PrevControllerState[static_cast<int>(Button)];
}

bool Input::ControllerButtonPressedDown(ControllerButton Button) 
{
    return _ControllerState[static_cast<int>(Button)];
}

bool Input::ControllerButtonJustReleased(ControllerButton Button) 
{
    return !_ControllerState[static_cast<int>(Button)] && _PrevControllerState[static_cast<int>(Button)];
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
void Input::KeyCallback(GLFWwindow* Window, int KbKey, int Scancode, int Action, int Mods)
{
    if (Action == GLFW_PRESS) 
    {
        _KeyState[KbKey] = true;
    } 
    else if (Action == GLFW_RELEASE) 
    {
        _KeyState[KbKey] = false;
    }
}

void Input::MouseButtonCallback(GLFWwindow* Window, int Button, int Action, int Mods)
{
    if (Action == GLFW_PRESS) 
    {
        _MouseState[Button] = true;
    } 
    else if (Action == GLFW_RELEASE) 
    {
        _MouseState[Button] = false;
    }
}

void Input::CursorPosCallback(GLFWwindow* Window, double XPos, double YPos) 
{
    _MouseX = XPos;
    _MouseY = YPos;
}

void Input::ScrollCallback(GLFWwindow* Window, double XOffset, double YOffset) 
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