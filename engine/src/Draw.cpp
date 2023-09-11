#include <string>
#include <vector>

#include "../lib/Draw.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/gtc/matrix_transform.hpp"

Draw::Draw()
{
    Forms.CreateShader("./engine/shader/Line.vert", "./engine/shader/Line.frag");
}

void Draw::DrawCircle(const Circle& Form, Color Colour, glm::mat4& Projection, glm::mat4& View, int Segments)
{
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    std::vector<float> Vertices;
    float AngleSlice = 2.0f * 3.14159265359f / static_cast<float>(Segments);
    for (int i = 0; i < Segments; ++i) 
    {
        float Angle1 = i * AngleSlice;
        float Angle2 = (i + 1) * AngleSlice;

        float x1 = Form.x + Form.r * cos(Angle1);
        float y1 = Form.y + Form.r * sin(Angle1);
        float x2 = Form.x + Form.r * cos(Angle2);
        float y2 = Form.y + Form.r * sin(Angle2);

        Vertices.push_back(x1);
        Vertices.push_back(y1);
        Vertices.push_back(x2);
        Vertices.push_back(y2);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    Forms.SetUniform4f("U_Color", Colour.r, Colour.g, Colour.b, Colour.a);
    
    glm::mat4 VP = Projection*View;
    Forms.SetUniformMat4f("U_Mvp",VP);

    glDrawArrays(GL_LINE_LOOP, 0, Segments * 2);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Draw::DrawRectangle(const Rectangle& Form, Color Colour, glm::mat4& Projection, glm::mat4& View, float Angle)
{
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    float Vertices[] = 
    {
        -Form.w/2,    -Form.h/2,
         Form.w/2,    -Form.h/2,
         Form.w/2,     Form.h/2,
        -Form.w/2,     Form.h/2
    };

    glm::mat4 Model = glm::translate(glm::mat4(1.0), glm::vec3(Form.x+Form.w/2.0f, Form.y+Form.h/2.0f, 0.0f));
    Model = glm::rotate(Model, Angle, glm::vec3(0, 0, 1));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Forms.SetUniform4f("U_Color", Colour.r, Colour.g, Colour.b, Colour.a);
    glm::mat4 MVP = Projection*View*Model;
    Forms.SetUniformMat4f("U_Mvp",MVP);

    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}