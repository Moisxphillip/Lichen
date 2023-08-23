#include "../lib/VertexBuffer.hpp"
#include "../lib/Renderer.hpp"

unsigned int VertexBuffer::_CurrentlyBound = 0;

VertexBuffer::VertexBuffer(const void* Data, unsigned int Size):
_Data(Data), _Size(Size)
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
    if(_CurrentlyBound != _RendererID)
    {
        _CurrentlyBound = _RendererID;
        glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
        glBufferData(GL_ARRAY_BUFFER, _Size, _Data, GL_STATIC_DRAW);
    }
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    _CurrentlyBound = 0;
}