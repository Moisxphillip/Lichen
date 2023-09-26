#ifndef LICHEN_PARTICLES
#define LICHEN_PARTICLES

#include <vector>
#include <algorithm>

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
        int _Index;
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

#endif//LICHEN_PARTICLES