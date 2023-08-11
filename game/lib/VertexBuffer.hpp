#ifndef LICHEN_VBO
#define LICHEN_VBO

class VertexBuffer
{
    private:
        unsigned int _RendererID;
        
    public:
        VertexBuffer(const void*, unsigned int);
        ~VertexBuffer();

        void Bind();
        void Unbind();

};

#endif// LICHEN_VBO