#ifndef LICHEN_PARTICLES
#define LICHEN_PARTICLES

#include <vector>
#include <algorithm>

#include "Color.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include "Tools.hpp"
#include "Vector2.hpp"
#include "Xrand.hpp"

enum class MovementLevel
{
    Simple,
    Intermediate,
    Heavy,
};

struct Particle
{
    Vector2 Size;
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Acceleration;
    float SpeedVariation;//%
    float AccelVariation;//%
    float Angle;//Around own center
    float Spread;//angle centered on the velocity
    float Duration;//S
    bool Windswept;//Affected by wind vector
    bool ColorInterpolation;
    Color StartColor;
    Color EndColor;
};

class ParticleManager
{
    private:
        struct _Particle
        {
            Vector2 Size, Position, Velocity, Acceleration;
            float Angle, Duration, TimeSpent;
            bool Active;
            bool Windswept;
            bool ColorInterpolation;
            Color StartColor;
            Color Average;
            Color EndColor;
        };
        std::vector<_Particle> _Particles;
        int _Index = 499;
        Vector2 _Wind;
        XrandF32 _Random;
        // Shader Forms;
        Image* _sprite;

    public:
        ParticleManager();
        ~ParticleManager();
        void Update(float Dt);
        void Render();
        void Emit(Particle& P);
        void WindSimulation();

};


// void ParticleManager::Render()
// {
    // unsigned int VAO, VBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);

    // float Vertices[] = 
    // {
    //     -Form.w/2,    -Form.h/2,
    //      Form.w/2,    -Form.h/2,
    //      Form.w/2,     Form.h/2,
    //     -Form.w/2,     Form.h/2
    // };

    // glm::mat4 Model = glm::translate(glm::mat4(1.0), glm::vec3(Form.x+Form.w/2.0f, Form.y+Form.h/2.0f, 0.0f));
    // Model = glm::rotate(Model, Angle, glm::vec3(0, 0, 1));

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_DYNAMIC_DRAW);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // Forms.SetUniform4f("U_Color", Colour.r, Colour.g, Colour.b, Colour.a);
    // glm::mat4 MVP = Projection*View*Model;
    // Forms.SetUniformMat4f("U_Mvp",MVP);

    // glDrawArrays(GL_LINE_LOOP, 0, 4);
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
// }

// #include "GLM/glm.hpp"
// #include "GLM/gtc/matrix_transform.hpp"

// void ParticleManager::Render()
// {
//     unsigned int VAO, VBO;
//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);

//     std::vector<float> ParticleData;

//     Forms.Bind();

//     // // Set uniform values that don't change per particle (e.g., projection, view).
//     // Forms.SetUniformMat4f("U_Projection", Projection);
//     // Forms.SetUniformMat4f("U_View", View);

//     for (const _Particle& particle : _Particles)
//     {
//         if (!particle.Active)
//             continue;

//         // Calculate the model matrix for the particle (translation, rotation, etc.)
//         glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(particle.Position.x, particle.Position.y, 0.0f));
//         Model = glm::rotate(Model, particle.Angle, glm::vec3(0, 0, 1));

//         // Set uniform values that may change for each particle (e.g., color).
//         Forms.SetUniform4f("U_Color", particle.Average.r, particle.Average.g, particle.Average.b, particle.Average.a);

//         particleData.push_back(particle.Position.x);
//         particleData.push_back(particle.Position.y);
//     }

//         // Set other particle-specific uniforms here if needed.
//         // Append particle data (e.g., vertex positions) to the particleData vector.
//         // The data format depends on how you intend to draw the quads.
//         // Note: You may need to transform the particle positions into quad vertices.
//         // Example: Append particle position for a quad (bottom-left corner).
//         // Repeat for other quad vertices or attributes.
//         // You can also use interleaved vertex data if applicable.
//     // Update VBO data with particleData (positions, colors, etc.)
//     glBufferData(GL_ARRAY_BUFFER, sizeof(float) * particleData.size(), particleData.data(), GL_DYNAMIC_DRAW);

//     // Draw all particles (quads) at once.
//     glDrawArrays(GL_TRIANGLES, 0, particleData.size() / numAttributes); // numAttributes depends on your data format.

//     glBindVertexArray(0); // Unbind the VAO
//     Forms.Unbind(); // Deactivate your shader program
// }








#endif//LICHEN_PARTICLES