#include "../lib/Renderer.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR); //Clear errors sequentially
}

bool GLCheckError()
{
    while (unsigned int ErrorCode = glGetError())
    {
        switch(ErrorCode) 
        {
            case GL_INVALID_ENUM :
                Error("[OpenGL] GL_INVALID_ENUM");
                break;
            case GL_INVALID_VALUE :
                Error("[OpenGL] GL_INVALID_OPERATION");
                break;
            case GL_INVALID_OPERATION :
                Error("[OpenGL] GL_INVALID_OPERATION");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION :
                Error("[OpenGL] GL_INVALID_FRAMEBUFFER_OPERATION");
                break;
            case GL_OUT_OF_MEMORY :
                Error("[OpenGL] GL_OUT_OF_MEMORY");
                break;
            case GL_STACK_UNDERFLOW :
                Error("[OpenGL] GL_STACK_UNDERFLOW");
                break;
            case GL_STACK_OVERFLOW :
                Error("[OpenGL] GL_STACK_OVERFLOW");
                break;
            default :
                Error("[OpenGL] Error: " + std::to_string(ErrorCode));
        }
        return false;
    }
    return true;
}

Renderer::Renderer()
{
    _ExitRequested = false;
    _View = new glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f)));
    _CurrBlend = BlendMode::None;
}
Renderer::~Renderer()
{
    delete _View;
}

bool Renderer::ExitRequested()
{
    return _ExitRequested;
}

void Renderer::SetClearColor(Color HexColor)
{
    glClearColor(HexColor.R/255.0,HexColor.G/255.0,HexColor.B/255.0,(255-HexColor.A)/255);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(VertexArray& Va, IndexBuffer& Ib, Shader& Sh)
{
    Sh.Bind();  //TODO verify if binding shader here is needed when using multiple shaders
    Va.Bind();
    Ib.Bind();
    glDrawElements(GL_TRIANGLES, Ib.GetCount(), GL_UNSIGNED_INT, nullptr);// to use with index buffers. If converting to short int, change the 3rd definition
}

void Renderer::Show(GLFWwindow* CurrWindow)
{
    glfwSwapBuffers(CurrWindow);
    glfwPollEvents();
    if(glfwWindowShouldClose(CurrWindow))
    {
        _ExitRequested = true;
    }
}

void Renderer::SetViewPosition(Vector2 Pos)
{
    *_View = glm::translate(glm::mat4(1.0f), glm::vec3(Pos.x,Pos.y,0.0f));
}

//TODO add more blend modes
void Renderer::SetBlendMode(BlendMode Blend)
{
    if(Blend!=_CurrBlend)
    {
        _CurrBlend=Blend;
        switch(Blend)
        {
            case None:
                break;
            case Add:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            default:
                break;
        }
    }
}

glm::mat4& Renderer::GetView()
{
    return *_View;
}