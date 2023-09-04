#ifndef LICHEN_DRAW
#define LICHEN_DRAW

#include "Rect.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include "Shader.hpp"
#include "GLM/glm.hpp"

class Draw
{
    private:
        Shader Forms;

    public:
        Draw();
        void DrawCircle(const Circle&, Color, int, glm::mat4&, glm::mat4&);
        void DrawRectangle(const Rect&, Color, glm::mat4&, glm::mat4&, float=0);
};

#endif//LICHEN_DRAW