#ifndef LICHEN_IBO
#define LICHEN_IBO

class IndexBuffer
{
    private:
        unsigned int _RendererID;
        unsigned int _Count;
        static unsigned int _CurrentlyBound;
    
    public:
        IndexBuffer(const unsigned int*, unsigned int);
        ~IndexBuffer();

        void Bind();
        void Unbind();
        unsigned int GetID();
        unsigned int GetCount();

};

#endif// LICHEN_IBO