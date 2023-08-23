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
        Renderer _Rend;
        GLFWwindow* _Window;
        glm::mat4* _Projection;

    public:
        Window(std::string, int=800, int=800, int=0, int=0);
        ~Window();
        GLFWwindow* GetWindow();
        int GetWidth();
        int GetHeight();
        glm::mat4& GetProjection();
};

#endif//LICHEN_WINDOW