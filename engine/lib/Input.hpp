#ifndef LICHEN_INPUT
#define LICHEN_INPUT

#include <iostream>
#include <map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Vector2.hpp"
#include "Enum.hpp"


class Input 
{
    private:
        Input();
        static Input* _InputM;
        static GLFWwindow* _Window;
        static bool _KeyState[static_cast<int>(Key::LastKey)];
        static int _PrevKeyState[static_cast<int>(Key::LastKey)];

        static bool _MouseState[static_cast<int>(MouseButton::LastButton)];
        static int _PrevMouseState[static_cast<int>(MouseButton::LastButton)];
        static double _MouseX, _MouseY;
        static MouseScroll _ScrollDirection;
        
        static bool _ControllerState[static_cast<int>(ControllerButton::LastButton)];
        static int _PrevControllerState[static_cast<int>(ControllerButton::LastButton)];
        static float _ControllerAxis[static_cast<int>(ControllerAxis::LastAxis)];
        static bool _Controller1On;
        static float _ControllerDeadzone;
        
        static std::map<int, Key> _KeyCode;
        static bool _QuitRequested;
        static int _Ctr;

        // GLFW callbacks for events
        static void KeyCallback(GLFWwindow*, int, int, int, int);
        static void MouseButtonCallback(GLFWwindow*, int, int, int);
        static void CursorPosCallback(GLFWwindow* , double, double);
        static void ScrollCallback(GLFWwindow* , double, double);
        static void WindowResizeCallback(GLFWwindow* , int, int);
        static void ControllerCallback(int, int);

    public:
        //General functions
        static Input& Instance();
        static void Init(GLFWwindow*);
        static void Update();
        static bool QuitRequested();

        // Key functions
        static bool KeyJustPressed(Key);
        static bool KeyPressedDown(Key);
        static bool KeyJustReleased(Key);
        static bool KeyReleased(Key);

        // Mouse functions
        static bool MouseJustPressed(MouseButton);
        static bool MousePressedDown(MouseButton);
        static bool MouseJustReleased(MouseButton);
        static bool MouseReleased(MouseButton);
        static bool MouseScrolled(MouseScroll);
        static Vector2 MousePosition();

        // Controller functions
        static bool ControllerButtonJustPressed(ControllerButton);
        static bool ControllerButtonPressedDown(ControllerButton);
        static bool ControllerButtonJustReleased(ControllerButton);
        static bool ControllerButtonReleased(ControllerButton);
        static void VibrateController(float, float);
        static void SetControllerButtonDeadzone(float);
        static float GetControllerAxis(ControllerAxis);
};

#endif//LICHEN_INPUT