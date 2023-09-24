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
        void DrawCircle(const Circle& Form, Color Colour, glm::mat4& Projection, glm::mat4& View, int Segments=25);
        void DrawLine(const Vector2& Origin, const Vector2& Span, Color Colour, glm::mat4& Projection, glm::mat4& View);
        void DrawRectangle(const Rectangle& Form, Color Colour, glm::mat4& Projection, glm::mat4& View, float Angle=0);
};

#endif//LICHEN_DRAW