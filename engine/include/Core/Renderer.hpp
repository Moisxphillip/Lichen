#ifndef LICHEN_RENDERER
#define LICHEN_RENDERER

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Tools/Tools.hpp"
#include "Tools/Color.hpp"
#include "Math//Vector2.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/IndexBuffer.hpp"
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
        void SetClearColor(Color Clear = (std::string)"#000000");
        void SetBlendMode(BlendMode Blend);
        void Draw(VertexArray& Va, IndexBuffer& Ib, Shader& Sh);
        void Show(GLFWwindow* _Window);
        void SetViewPosition(Vector2 ViewPos);
        glm::mat4& GetView();

};

#endif//LICHEN_RENDERER