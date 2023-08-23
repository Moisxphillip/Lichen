#ifndef LICHEN_VAO
#define LICHEN_VAO

#include "../lib/VertexBuffer.hpp"
#include "../lib/VertexBufferLayout.hpp"

class VertexArray
{
    private:
        unsigned int _RendererID;
        static unsigned int _CurrentlyBound;
        
    public:
        VertexArray();
        ~VertexArray();
        void Bind();
        void Unbind();
        void AddBuffer(VertexBuffer&, VertexBufferLayout&);
};


#endif//LICHEN_VAO