#ifndef LICHEN_VBL
#define LICHEN_VBL

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct VBElement
{
    unsigned int Count;
    unsigned int Type;
    unsigned char Normalized;
    static unsigned int SizeOfType(unsigned int);
};

class VertexBufferLayout
{
    private:
        std::vector<VBElement> _Elements;
        unsigned int _Stride;

    public:
        VertexBufferLayout();
        unsigned int GetStride();
        std::vector<VBElement> GetElements();

        void Push(unsigned int, unsigned int);

};


#endif//LICHEN_VBL