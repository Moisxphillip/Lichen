#ifndef LICHEN_RENDERER
#define LICHEN_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../lib/Tools.hpp"
#include "../lib/Color.hpp"
#include "../lib/Vector2.hpp"
#include "../lib/Shader.hpp"
#include "../lib/VertexArray.hpp"
#include "../lib/IndexBuffer.hpp"
// #include <string>

void GLClearError();
bool GLCheckError();

enum BlendMode
{
    None = 0,
    Add = 1,
};

class Renderer
{
    private:
        glm::mat4* _View;
        BlendMode _CurrBlend;
        
    public:
        Renderer();
        ~Renderer();
        void Clear();
        void SetClearColor(Color=(std::string)"#000000");
        void SetBlendMode(BlendMode);
        void Draw(VertexArray&, IndexBuffer&, Shader&);
        void Show(GLFWwindow*);
        void SetViewPosition(Vector2);
        glm::mat4& GetView();

};

#endif//LICHEN_RENDERER