#include "Core/Window.hpp"
#include <iostream>
Window::Window(std::string WindowName, int Width, int Height, int ProjWidth, int ProjHeight, bool VSync)
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

    _Window = glfwCreateWindow(Width, Height, WindowName.c_str(),0,0);

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

    // glEnable(GL_DEPTH_TEST); //For 3D Depth
    _ProjectionWidth = (ProjWidth != 0 ? ProjWidth  : Width ); //In case there's internal resolution
    _ProjectionHeight = (ProjHeight != 0 ? ProjHeight : Height);

    int x=0,y=0, w=_Width, h=_Height;
    float DesiredRatio = (float)_ProjectionWidth/(float)_ProjectionHeight;
    float AspectRatio = (float)_Width/(float)_Height;
    std::cout <<'\0';// there's a heisenbug in release mode that is fixed by this line '-'

    if(DesiredRatio < AspectRatio)
    {
        int nW = (int)(_Width * DesiredRatio);
        x = (_Width - nW)/2;
        y = 0;
        w = nW;
    }
    else if(DesiredRatio > AspectRatio)
    {
        int nH = (int)(_Height/DesiredRatio);
        x = 0;
        y = (_Height - nH)/2;
        h = nH;
    }
    
    glViewport(x,y,w,h);
    
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

int  Window::GetProjectionWidth()
{
    return _ProjectionWidth;
}

int  Window::GetProjectionHeight()
{
    return _ProjectionHeight;
}

void  Window::SetWidth(int W)
{
    _Width = W;
}

void  Window::SetHeight(int H)
{
    _Height = H;
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