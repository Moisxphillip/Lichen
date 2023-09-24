#include "Graphics/VertexBuffer.hpp"
#include "Core/Renderer.hpp"



VertexBuffer::VertexBuffer(const void* Data, unsigned int Size, DrawMode DrawAs):
_Data(Data), _Size(Size)
{
    _DrawAs = DrawAs;
    glGenBuffers(1,&_RendererID); //ID for the object in the buffer
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);//next step is to specify the data
    glBufferData(GL_ARRAY_BUFFER, Size, Data, DrawAs);//stream for few modifications and use, static for more use, dynamic for lots of both
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
    glBufferData(GL_ARRAY_BUFFER, _Size, _Data, _DrawAs);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}