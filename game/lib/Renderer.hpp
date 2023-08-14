#ifndef LICHEN_RENDERER
#define LICHEN_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../../engine/lib/Tools.hpp"
#include "../lib/Shader.hpp"
#include "../lib/VertexArray.hpp"
#include "../lib/IndexBuffer.hpp"

void GLClearError();
bool GLCheckError();


class Renderer
{
    private:

    public:
        void Clear();
        void Draw(VertexArray&, IndexBuffer&, Shader&);

};

#endif//LICHEN_RENDERER