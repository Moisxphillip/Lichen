#include "../lib/Window.hpp"

Window::Window(std::string Name, int Width, int Height, int ProjectionWidth, int ProjectionHeight)
{
    _Width = Width;
    _Height = Height;

    if(!glfwInit())
    {
        Error("Window::Window: GLFW init failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //hints for the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //must have a vertex array if using this

    _Window = glfwCreateWindow(Width, Height, Name.c_str(),0,0);

    if(!_Window)
    {
        Error("Window::Window: Window creation failed");
    }

    glfwMakeContextCurrent(_Window);
    glfwSwapInterval(0); //VSync

    if(glewInit()!=GLEW_OK)//glew comes after making the context
    {
        Error("Window::Window: GLEW init failed");
    }

    (ProjectionWidth  != 0 ? _ProjectionWidth  = ProjectionWidth  : _ProjectionWidth  = Width );
    (ProjectionHeight != 0 ? _ProjectionHeight = ProjectionHeight : _ProjectionHeight = Height);

    _Projection = new glm::mat4(glm::ortho( //x = ➡, y = ⬇
        0.0f, (float)_ProjectionWidth,  //X
        (float)_ProjectionHeight, 0.0f, //Y
        0.0f, 10.0f                     //Z
    ));
}

Window::~Window()
{
    delete _Projection;
    glfwDestroyWindow(_Window);
    glfwTerminate();
}

GLFWwindow* Window::GetWindow()
{
    return _Window;
}

int  Window::GetWidth()
{
    return _Width;
}

int  Window::GetHeight()
{
    return _Height;
}

glm::mat4& Window::GetProjection()
{
    return *_Projection;
}