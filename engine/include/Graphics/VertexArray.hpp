#ifndef LICHEN_VAO
#define LICHEN_VAO

#include "Graphics/VertexBuffer.hpp"
#include "Graphics/VertexBufferLayout.hpp"

class VertexArray
{
    private:
        unsigned int _RendererID;
        
    public:
        VertexArray();
        ~VertexArray();
        void Bind();
        void Unbind();
        void AddBuffer(VertexBuffer&, VertexBufferLayout&);
};


#endif//LICHEN_VAO