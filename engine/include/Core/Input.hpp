#ifndef LICHEN_INPUT
#define LICHEN_INPUT

#include <iostream>
#include <map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Math/Vector2.hpp"
#include "Core/Enum.hpp"


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
        static bool _Fullscreen;

        // GLFW callbacks for events
        static void KeyCallback(GLFWwindow* GLWindow, int KbKey, int Scancode, int Action, int Mods);
        static void MouseButtonCallback(GLFWwindow* GLWindow, int Button, int Action, int Mods);
        static void CursorPosCallback(GLFWwindow* GLWindow, double XPos, double YPos);
        static void ScrollCallback(GLFWwindow* GLWindow, double XOffset, double YOffset);
        static void WindowResizeCallback(GLFWwindow* GLWindow, int W, int H);
        static void ControllerCallback(int ID, int Event);

    public:
        //General functions
        static Input& Instance();
        static void Init(GLFWwindow* _Window);
        static void Update();
        static bool QuitRequested();

        // Key functions
        static bool KeyJustPressed(Key Value);
        static bool KeyPressedDown(Key Value);
        static bool KeyJustReleased(Key Value);
        static bool KeyReleased(Key Value);

        // Mouse functions
        static bool MouseJustPressed(MouseButton Value);
        static bool MousePressedDown(MouseButton Value);
        static bool MouseJustReleased(MouseButton Value);
        static bool MouseReleased(MouseButton Value);
        static bool MouseScrolled(MouseScroll Value);
        static Vector2 MousePosition();

        // Controller functions
        static bool ControllerButtonJustPressed(ControllerButton Value);
        static bool ControllerButtonPressedDown(ControllerButton Value);
        static bool ControllerButtonJustReleased(ControllerButton Value);
        static bool ControllerButtonReleased(ControllerButton Value);
        static void VibrateController(float X, float Y);// No support yet
        static void SetControllerButtonDeadzone(float Deadzone);
        static float GetControllerAxis(ControllerAxis Value);
};

#endif//LICHEN_INPUT