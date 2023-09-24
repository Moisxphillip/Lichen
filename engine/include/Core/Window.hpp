#ifndef LICHEN_WINDOW
#define LICHEN_WINDOW

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Core/Renderer.hpp"

class Window
{
    private:
        int _Width, _Height;
        int _ProjectionWidth, _ProjectionHeight;
        GLFWwindow* _Window;
        glm::mat4* _Projection;

    public:
        Window(std::string WindowName, int Width=800, int Height=800, int ProjWidth=0, int ProjHeight=0, bool VSync=false);
        ~Window();
        GLFWwindow* GetGLWindow();
        int GetWidth();
        int GetHeight();
        int GetProjectionWidth();
        int GetProjectionHeight();
        void SetWidth(int Width);
        void SetHeight(int Height);
        bool QuitRequested();
        void SetProjection(glm::mat4& NewProjection);
        glm::mat4& GetProjection();
};

#endif//LICHEN_WINDOW