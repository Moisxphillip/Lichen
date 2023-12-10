#ifndef LICHEN_PARTICLES
#define LICHEN_PARTICLES

#include <vector>
#include <algorithm>

#include "Components/Sprite.hpp"
#include "Tools/Color.hpp"
#include "Tools/Tools.hpp"
#include "Tools/Xrand.hpp"
#include "Graphics/Image.hpp"
#include "Math/Vector2.hpp"

struct Particle
{
    unsigned int Type = 0;
    Vector2 Size = Vector2(1.0f, 1.0f);
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Acceleration;
    float SpeedVariation = 0;//%
    float AccelVariation = 0;//%
    float Angle = 0;//Around own center
    float RotationPerSec = 0;//How much should rotate
    float Spread = 0;//angle centered on the velocity
    float Duration = 0;//S
    bool Windswept = false;//Affected by wind vector
    bool ColorInterpolation = false;
    Color StartColor;
    Color EndColor;
};

class ParticleManager
{
    private:
        struct _Particle
        {
            unsigned int Type;
            Vector2 Size, Position, Velocity, Acceleration;
            float Angle, RotationPerSec, Duration, TimeSpent;
            bool Active;
            bool Windswept;
            bool ColorInterpolation;
            Color StartColor;
            Color Average;
            Color EndColor;
        };
        static std::vector<_Particle> _Particles;
        static int _Index;
        static Vector2 _Wind;
        static XrandF32 _Random;
        // Shader Forms;
        // Image* _sprite;
        static GameObject* _Obj;
        static Sprite* _Sprite;
        static ParticleManager* _Self;
        static void _WindSimulation();

    public:
        ParticleManager();
        ~ParticleManager();
        static ParticleManager& Instance();
        static void Update(float Dt);
        static void Render();
        static void Emit(Particle& P);
};

class PremadeParticles
{
    public:
        static Particle Leaf(Vector2 Position);
        static Particle Spore(Vector2 Position);
        static Particle Energy(Vector2 Position);

};


#endif//LICHEN_PARTICLES