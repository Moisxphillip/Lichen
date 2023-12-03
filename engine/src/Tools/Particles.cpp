#include "Tools/Particles.hpp"
#include "Core/Engine.hpp"

// Particle::Particle()
// : Size(0.0f, 0.0f), Position(0.0f, 0.0f), Velocity(0.0f, 0.0f), Acceleration(0.0f, 0.0f),
// Angle(0.0f), Duration(0.0f), Windswept(false), StartColor("#ffffff"), EndColor("#ffffff")
// {}

// ParticleManager::_Particle::_Particle()
// : Size(0.0f, 0.0f), Position(0.0f, 0.0f), Velocity(0.0f, 0.0f), Acceleration(0.0f, 0.0f), Angle(0.0f), Duration(0.0f),
// TimeSpent(0.0f), Active(false), Windswept(false), StartColor("#ffffff"), EndColor("#ffffff"), Average(StartColor)
// {}
#include <ctime>

std::vector<ParticleManager::_Particle> ParticleManager::_Particles;
int ParticleManager::_Index;
Vector2 ParticleManager::_Wind;
XrandF32 ParticleManager::_Random(static_cast<unsigned long long int>(std::time(nullptr))); //TODO Seed properly later
GameObject* ParticleManager::_Obj;
Sprite* ParticleManager::_Sprite;
ParticleManager* ParticleManager::_Self = nullptr;

#include <ctime>

ParticleManager::ParticleManager()
{
    _Index = 499;
    _Particles.resize(_Index+1);
    _Random.seed(static_cast<unsigned long long int>(std::time(nullptr)));
    _Obj = new GameObject();
    _Sprite = new Sprite(*_Obj, "./engine/res/particle_4x4f_16.16px.png", 16, 4, 4);
    _Wind = Vector2(0.0f,1.0f);
}

ParticleManager::~ParticleManager()
{
    delete _Sprite;
    delete _Obj;
    delete _Self;
}

ParticleManager& ParticleManager::Instance()
{
    if(_Self == nullptr)
    {
        _Self = new ParticleManager();
    }
    return *_Self;
}

void ParticleManager::Update(float Dt)
{
    _WindSimulation();
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
        P.TimeSpent += Dt;
        
        if(P.Windswept)
        {
            P.Velocity+=_Wind*Dt;
        }
        P.Velocity += P.Acceleration *Dt;
        P.Position += P.Velocity *Dt;
        P.Angle += P.RotationPerSec*Dt;

        // if(P.Windswept)
        // {
        //     P.Position+=_Wind*Dt;
        // }

        if (P.ColorInterpolation)
        {
            P.Average = Color::Interpolation(P.StartColor, P.EndColor, std::clamp(P.TimeSpent/P.Duration, 0.0f, 1.0f));
        }

    }
}

void ParticleManager::Emit(Particle& Part)
{
    _Particle& P = _Particles[_Index];
    P.Type = static_cast<unsigned int>(Part.Type);
    P.Active = true;
    P.Size = Part.Size;

    P.Acceleration = Part.Acceleration;//Add variation;
    P.Velocity = Part.Velocity.Rotate(_Random.gen()*Part.Spread - Part.Spread/2.0f);//Add variation;
    P.Position = Part.Position;
    P.Duration = Part.Duration;
    P.Angle = Part.Angle;
    P.RotationPerSec = Part.RotationPerSec;

    P.ColorInterpolation = Part.ColorInterpolation;
    P.StartColor = Part.StartColor;
    P.Average = P.StartColor;
    P.EndColor = Part.EndColor;

    P.Windswept = Part.Windswept;
    P.TimeSpent = 0.0f;
    //TODO Check a better way to assync them
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
        
        if(_Sprite->GetCurrentFrame() != _Particles[i].Type)
        {
            _Sprite->SetFrame(_Particles[i].Type);
        }
        _Sprite->SetColor(_Particles[i].Average);
        _Sprite->SetScale(_Particles[i].Size);
        _Sprite->Render(_Particles[i].Position.x, _Particles[i].Position.y, _Particles[i].Angle);
        // _sprite->SetColor(_Particles[i].Average);
        // _sprite->Render(Engine::Instance().GetRenderer(), Engine::Instance().GetWindow().GetProjection(),
        // _Particles[i].Position, _Particles[i].Size, ___ImageRect{0,0,43,44}, _Particles[i].Angle);
    }
}

#define WIND_SPEED 200
#define WIND_VARIATION 20

#include <iostream>
void ParticleManager::_WindSimulation()
{
    if(Engine::Instance().GetPing())
    {
        _Wind.Normalize();
        Vector2 Var = _Wind * WIND_VARIATION * (_Random.gen()-0.5f);
        _Wind = _Wind * WIND_SPEED + Var;
        _Wind.Rotate(3.1415/2*(_Random.gen()-0.5f));
        // std::cout << _Wind << '\n';
    }
}
