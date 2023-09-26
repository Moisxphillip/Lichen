#ifndef LICHEN_VBO
#define LICHEN_VBO

#include "Core/Enum.hpp"

class VertexBuffer
{
    private:
        unsigned int _RendererID;
        unsigned int _Size;
        const void* _Data;
        DrawMode _DrawAs;
        
    public:
        VertexBuffer(const void* Data, unsigned int Size, DrawMode DrawAs);
        ~VertexBuffer();

        void Bind();
        void Unbind();

};

#endif// LICHEN_VBO