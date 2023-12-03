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

enum class MovementLevel
{
    Simple,
    Intermediate,
    Heavy,
};

struct Particle
{
    unsigned int Type;
    Vector2 Size;
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Acceleration;
    float SpeedVariation;//%
    float AccelVariation;//%
    float Angle;//Around own center
    float RotationPerSec;//How much should rotate
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

#endif//LICHEN_PARTICLES