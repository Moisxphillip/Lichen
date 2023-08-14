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

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(VertexArray& Va, IndexBuffer& Ib, Shader& Sh)
{
    Sh.Bind(); 
    Va.Bind();
    Ib.Bind();
    glDrawElements(GL_TRIANGLES, Ib.GetCount(), GL_UNSIGNED_INT, nullptr);// to use with index buffers. If converting to short int, change the 3rd definition
}