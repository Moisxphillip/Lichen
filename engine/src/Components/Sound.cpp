#include "Components/Sound.hpp"
#include "Core/Engine.hpp"
#include "Core/Resources.hpp"
#include "Tools/Tools.hpp"

#include <algorithm>

float Sound::_EarDistance = 256;
float Sound::_LMaxRadius = 800.0f;
float Sound::_LMinRadius = 180.0f / _LMaxRadius;
float Sound::_MaxRadius = _LMaxRadius * _LMaxRadius;
float Sound::_MinRadius = _LMinRadius * _LMinRadius / _MaxRadius;

Sound::Sound(GameObject& GameObj)
: Component(GameObj)
{
    Pan = false;
    Linear = true;
    SelfDestruct = false;
    _SoundChunk = nullptr;
    _SoundVolume = 255;
    _Type = ComponentType::Sound;
}

Sound::Sound(GameObject& GameObj, std::string File)
: Sound(GameObj)
{
    Open(File);
}

Sound::~Sound()
{
    Stop();
}


void Sound::Play(int Times)
{
    //Channel finding is handled by our class, since we need control over the chunk settings
    for(int i = 0; i<Engine::Instance().GetSoundChannels(); i++)
    {
        if(Mix_Playing(i) == 0)//Found a free channel
        {
            Mix_Volume(i, _SoundVolume);
            _SoundChannel = Mix_PlayChannel(i, _SoundChunk, Times);
            return;
        }
    }
    Error("Sound::Play: Could not find an empty channel");
}

void Sound::Stop()
{
    if(_SoundChunk != nullptr && IsPlaying())
    {
        Mix_HaltChannel(_SoundChannel);
    }
}

void Sound::Volume(int NewVolume)
{
    _SoundVolume = NewVolume;
}

void Sound::Open(std::string File)
{
    _SoundChunk = Resources::GetSound(File);
    if(_SoundChunk == nullptr)
    {
        Error("Sound::Load: Mix_LoadWAV could not load the soundchunk "+File);
    }
}

bool Sound::IsOpen()
{
    return (_SoundChunk != nullptr);
}

bool Sound::IsPlaying()
{
    return (Mix_Playing(_SoundChannel) != 0);
}

void Sound::SetVolume(int Volume)
{
    if(Pan)
    {
        Error("Sound::SetVolume: Trying to set volume on an automatic Pan object");
    }
    _SoundVolume = std::clamp(Volume, 0, 255);
}

//Position-based sound pan&volume control
void Sound::_SoundPosition()
{
    Vector2 Pos = Engine::Instance().CurrentScene().Cam.Position()
        + Vector2(Engine::Instance().GetWindow().GetProjectionWidth()/2, Engine::Instance().GetWindow().GetProjectionHeight()/2);

    if(Linear)
    {
        float DistL = std::abs(Parent.Box.Center().x - Pos.x - _EarDistance/2) + std::abs(Parent.Box.Center().y - Pos.y);
        float DistR = std::abs(Parent.Box.Center().x - Pos.x + _EarDistance/2) + std::abs(Parent.Box.Center().y - Pos.y);
        float LVol = std::max(std::min(-DistL / _LMaxRadius + 1 + _LMinRadius, 1.f), 0.f);
        float RVol = std::max(std::min(-DistR / _LMaxRadius + 1 + _LMinRadius, 1.f), 0.f);
        Mix_SetPanning(_SoundChannel,(int)(RVol*255), (int)(LVol*255));
        return;
    }

    float SqDistL = std::pow(Parent.Box.Center().x - Pos.x - _EarDistance/2, 2) + std::pow(Parent.Box.Center().y - Pos.y, 2);
    float SqDistR = std::pow(Parent.Box.Center().x - Pos.x + _EarDistance/2, 2) + std::pow(Parent.Box.Center().y - Pos.y, 2);
    float LVol = std::max(std::min(-SqDistL/_MaxRadius + 1 + _MinRadius, 1.f),0.f);
    float RVol = std::max(std::min(-SqDistR/_MaxRadius + 1 + _MinRadius, 1.f),0.f);
    Mix_SetPanning(_SoundChannel,(int)(RVol*255), (int)(LVol*255));
}

//Inheritance Functions
void Sound::Update(float Dt)
{
    if(IsPlaying())
    {
        if(Pan)
        {
            _SoundPosition();
        }
    }
    else
    {
        if(SelfDestruct)
        {
            Parent.RequestDelete();  
        }
    }    
}
