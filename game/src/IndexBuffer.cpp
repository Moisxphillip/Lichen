#include "../lib/IndexBuffer.hpp"
#include "../lib/Renderer.hpp"


unsigned int IndexBuffer::_CurrentlyBound = 0;

IndexBuffer::IndexBuffer(const unsigned int *Data, unsigned int Count)
{
    _Count = Count;
    glGenBuffers(1,&_RendererID); //ID for the object in the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);//next step is to specify the data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), Data, GL_STATIC_DRAW);//stream for few modifications and use, static for more use, dynamic for lots of both
}

IndexBuffer::~IndexBuffer()
{
    Unbind();
    glDeleteBuffers(1, &_RendererID);
}

void IndexBuffer::Bind()
{
    if(_CurrentlyBound != _RendererID)
    {
        _CurrentlyBound = _RendererID;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);
    }
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    _CurrentlyBound = 0;
}

unsigned int IndexBuffer::GetID()
{
    return _RendererID;
}

unsigned int IndexBuffer::GetCount()
{
    return _Count;
}