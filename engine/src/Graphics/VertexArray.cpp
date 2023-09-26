#include "Graphics/VertexArray.hpp"

//controversy: structure is recommended by opengl, but using a global VAO and binding 
//new forms is faster in performance. If slow, benchmark and substitute for globals.


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_RendererID);
}

VertexArray::~VertexArray()
{
    Unbind();
    glDeleteVertexArrays(1, &_RendererID);
}

void VertexArray::Bind()
{
    glBindVertexArray(_RendererID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer& Vb, VertexBufferLayout& Vbl)
{
    Bind();
    Vb.Bind();
    const auto& Elements = Vbl.GetElements();
    unsigned int Offset = 0;
    for(unsigned int i = 0; i < Elements.size(); i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, Elements[i].Count, Elements[i].Type,
            Elements[i].Normalized, Vbl.GetStride(), (const void*) Offset);
        Offset+= Elements[i].Count * VBElement::SizeOfType(Elements[i].Type);
    }
}