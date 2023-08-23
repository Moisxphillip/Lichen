#ifndef LICHEN_RENDERER
#define LICHEN_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../../engine/lib/Tools.hpp"
#include "../../engine/lib/Color.hpp"
#include "../../engine/lib/Vector2.hpp"
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
        bool _ExitRequested;
        glm::mat4* _View;
        BlendMode _CurrBlend;
        
    public:
        Renderer();
        ~Renderer();
        bool ExitRequested();
        void Clear();
        void SetClearColor(Color=(std::string)"#000000");
        void SetBlendMode(BlendMode);
        void Draw(VertexArray&, IndexBuffer&, Shader&);
        void Show(GLFWwindow*);
        void SetViewPosition(Vector2);
        glm::mat4& GetView();

};

#endif//LICHEN_RENDERER