#include <string>
#include <vector>

#include "../lib/Draw.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

Draw::Draw()
{
    Forms.CreateShader("./engine/shader/Line.vert", "./engine/shader/Line.frag");
}

void Draw::DrawCircle(const Circle& Form, Color Colour, int Segments, glm::mat4& Projection, glm::mat4& View)
{
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    std::vector<float> vertices;
    float AngleSlice = 2.0f * 3.14159265359f / static_cast<float>(Segments);
    for (int i = 0; i < Segments; ++i) 
    {
        float Angle1 = i * AngleSlice;
        float Angle2 = (i + 1) * AngleSlice;

        float x1 = Form.x + Form.r * cos(Angle1);
        float y1 = Form.y + Form.r * sin(Angle1);
        float x2 = Form.x + Form.r * cos(Angle2);
        float y2 = Form.y + Form.r * sin(Angle2);

        vertices.push_back(x1);
        vertices.push_back(y1);
        vertices.push_back(x2);
        vertices.push_back(y2);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    Forms.SetUniform4f("color", Colour.r, Colour.g, Colour.b, Colour.a);
    
    glm::mat4 VP = Projection*View;
    Forms.SetUniformMat4f("U_Mvp",VP);

    glDrawArrays(GL_LINE_LOOP, 0, Segments * 2);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Draw::DrawRectangle(const Rect& Form, Color Colour, glm::mat4& Projection, glm::mat4& View)
{
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    GLfloat vertices[] = 
    {
        Form.x,             Form.y,
        Form.x + Form.w,    Form.y,
        Form.x + Form.w,    Form.y + Form.h,
        Form.x,             Form.y + Form.h
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    Forms.SetUniform4f("color", Colour.r, Colour.g, Colour.b, Colour.a);
    glm::mat4 VP = Projection*View;
    Forms.SetUniformMat4f("U_Mvp",VP);

    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}