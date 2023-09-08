#ifndef LICHEN_WINDOW
#define LICHEN_WINDOW

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Renderer.hpp"

class Window
{
    private:
        int _Width, _Height;
        int _ProjectionWidth, _ProjectionHeight;
        GLFWwindow* _Window;
        glm::mat4* _Projection;

    public:
        Window(std::string, int=800, int=800, int=0, int=0, bool=false);
        ~Window();
        GLFWwindow* GetGLWindow();
        int GetWidth();
        int GetHeight();
        bool QuitRequested();
        void SetProjection(glm::mat4&);
        glm::mat4& GetProjection();
};

#endif//LICHEN_WINDOW