#include "Graphics/VertexBufferLayout.hpp"

unsigned int VBElement::SizeOfType(unsigned int Type)
{
    switch(Type)
    {
        case GL_FLOAT: 
            return sizeof(GLfloat);
        
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        
        case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte);
    }
    return 0;
}


VertexBufferLayout::VertexBufferLayout()
{
    _Stride = 0;
}

unsigned int VertexBufferLayout::GetStride()
{
    return _Stride;
}

std::vector<VBElement> VertexBufferLayout::GetElements()
{
    return _Elements;
}

void VertexBufferLayout::Push(unsigned int Type, unsigned int Count)
{
    _Elements.push_back({Count, Type, GL_FALSE});
    _Stride += VBElement::SizeOfType(Type) * Count;
}