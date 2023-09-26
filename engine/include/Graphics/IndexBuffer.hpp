#ifndef LICHEN_IBO
#define LICHEN_IBO

class IndexBuffer
{
    private:
        unsigned int _RendererID;
        unsigned int _Count;
    
    public:
        IndexBuffer(const unsigned int *Data, unsigned int Count);
        ~IndexBuffer();

        void Bind();
        void Unbind();
        unsigned int GetID();
        unsigned int GetCount();

};

#endif// LICHEN_IBO