#include "../lib/VertexBuffer.hpp"
#include "../lib/Renderer.hpp"

VertexBuffer::VertexBuffer(const void* Data, unsigned int Size)
{
    glGenBuffers(1,&_RendererID); //ID for the object in the buffer
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);//next step is to specify the data
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);//stream for few modifications and use, static for more use, dynamic for lots of both
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}