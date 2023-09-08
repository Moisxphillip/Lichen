#include "../lib/Window.hpp"

Window::Window(std::string Name, int Width, int Height, int ProjectionWidth, int ProjectionHeight, bool VSync)
{
    _Width = Width;
    _Height = Height;

    if(!glfwInit())
    {
        Error("Window::Window: GLFW init failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //hints for the _Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //must have a vertex array if using this

    _Window = glfwCreateWindow(Width, Height, Name.c_str(),0,0);

    if(!_Window)
    {
        Error("Window::Window: Window creation failed");
    }

    glfwMakeContextCurrent(_Window);
    glfwSwapInterval((int)VSync); //VSync

    if(glewInit()!=GLEW_OK)//glew comes after making the context
    {
        Error("Window::Window: GLEW init failed");
    }

    (ProjectionWidth  != 0 ? _ProjectionWidth  = ProjectionWidth  : _ProjectionWidth  = Width ); //In case there's internal resolution...
    (ProjectionHeight != 0 ? _ProjectionHeight = ProjectionHeight : _ProjectionHeight = Height);

    _Projection = new glm::mat4(glm::ortho( //X = ➡, Y = ⬇
        0.0f, (float)_ProjectionWidth,  //X
        (float)_ProjectionHeight, 0.0f, //Y
        -1000.0f, 1000.0f               //Z
    ));
        
}

Window::~Window()
{
    delete _Projection;
    glfwDestroyWindow(_Window);
    glfwTerminate();
}

GLFWwindow* Window::GetGLWindow()
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
bool Window::QuitRequested()
{
    glfwPollEvents(); //Must be here when you're not using input, otherwise the polling never occurs
    return glfwWindowShouldClose(_Window);
}

void Window::SetProjection(glm::mat4& Target)
{
    *_Projection = Target;
}

glm::mat4& Window::GetProjection()
{
    return *_Projection;
}