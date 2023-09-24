#ifndef LICHEN_DRAW
#define LICHEN_DRAW

#include "Math/Rectangle.hpp"
#include "Math/Circle.hpp"
#include "Tools/Color.hpp"
#include "Graphics/Shader.hpp"
#include "GLM/glm.hpp"

class Draw
{
    private:
        Shader Forms;

    public:
        Draw();
        void DrawCircle(const Circle&, Color, glm::mat4&, glm::mat4&, int=25);
        void DrawLine(const Vector2&, const Vector2&, Color, glm::mat4&, glm::mat4&);
        void DrawRectangle(const Rectangle&, Color, glm::mat4&, glm::mat4&, float=0);
};

#endif//LICHEN_DRAW