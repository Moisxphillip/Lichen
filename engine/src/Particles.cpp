#include "../lib/Particles.hpp"
#include "../lib/Engine.hpp"

// Particle::Particle()
// : Size(0.0f, 0.0f), Position(0.0f, 0.0f), Velocity(0.0f, 0.0f), Acceleration(0.0f, 0.0f),
// Angle(0.0f), Duration(0.0f), Windswept(false), StartColor("#ffffff"), EndColor("#ffffff")
// {}

// ParticleManager::_Particle::_Particle()
// : Size(0.0f, 0.0f), Position(0.0f, 0.0f), Velocity(0.0f, 0.0f), Acceleration(0.0f, 0.0f), Angle(0.0f), Duration(0.0f),
// TimeSpent(0.0f), Active(false), Windswept(false), StartColor("#ffffff"), EndColor("#ffffff"), Average(StartColor)
// {}

ParticleManager::ParticleManager()
{
    _Particles.resize(_Index+1);
    _Random.seed(42);//TODO seed properly later
    _sprite = new Image("./res/img/particle.png");
    _Wind = Vector2(-95,30);
}
ParticleManager::~ParticleManager()
{
    delete _sprite;
}

void ParticleManager::Update(float Dt)
{
    for(int i = _Particles.size()-1; i>=0; i--)
    {
        if(!_Particles[i].Active)
        {
            continue;
        }
        if(_Particles[i].TimeSpent>=_Particles[i].Duration)
        {
            _Particles[i].Active = false;
            continue;
        }

        _Particle& P = _Particles[i];
        P.TimeSpent+=Dt;
        
        P.Velocity +=P.Acceleration *Dt;
        P.Position +=P.Velocity *Dt;
        P.Angle+=Dt;
        if(P.Windswept)
        {
            P.Position+=_Wind*Dt;
        }

        if (P.ColorInterpolation)
        {
            P.Average = Color::Interpolation(P.StartColor, P.EndColor, std::clamp(P.TimeSpent/P.Duration, 0.0f, 1.0f));
        }

    }
}

void ParticleManager::Emit(Particle& Part)
{
    _Particle& P = _Particles[_Index];
    P.Active = true;
    P.Size = Part.Size;
    P.Acceleration = Part.Acceleration;//Add variation;
    P.Velocity = Part.Velocity.Rotate(_Random.gen()*Part.Spread - Part.Spread/2.0f);//Add variation;
    P.Position = Part.Position;
    P.Duration = Part.Duration;
    P.Angle = Part.Angle;
    P.ColorInterpolation = Part.ColorInterpolation;
    P.StartColor = Part.StartColor;
    P.Average = P.StartColor;
    P.EndColor = Part.EndColor;
    P.Windswept = Part.Windswept;
    P.TimeSpent = 0.0f;
    P.Velocity.x+= _Random.gen()-0.5f;
    P.Velocity.y+= _Random.gen()-0.5f;

    _Index--;
    if(_Index<0)
    {
        _Index%=_Particles.size();
    }
}

void ParticleManager::Render()
{
    for(int i = _Particles.size()-1; i>=0; i--)
    {
        if(!_Particles[i].Active)
            continue;
        _sprite->SetColor(_Particles[i].Average);
        _sprite->Render(Engine::Instance().GetRenderer(), Engine::Instance().GetWindow().GetProjection(),
        _Particles[i].Position, _Particles[i].Size, ___ImageRect{0,0,43,44}, _Particles[i].Angle);
    }
}