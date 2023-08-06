#include "../lib/Sound.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"

Sound::Sound(GameObject& GameObj)
: Component(GameObj)
{
    Pan = false;
    SelfDestruct = false;
    _SoundChunk = nullptr;
    _SoundVolume = 255;
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


void Sound::Play(int Times = 0)
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

//Position-based sound pan&volume control
void Sound::_SoundPosition()
{
    //Set volume for each channel based on the gameobject center position
    float SoundPos = Parent.Box.Center().x - Engine::Instance().CurrentState().Cam.Position.x;
    
    int Location = (SoundPos/Engine::Instance().GetRenderSize().x * 400.f);
    (Location < 0 ? Location = 0 : (Location > 400 ? Location = 400 : Location));
    Location-=200;

    int R = 255 + Location;
    R>255?R=255:R;
    
    int L = 255 - Location;            
    L>255?L=255:L;

    Mix_SetPanning(_SoundChannel, L, R);
}

//Inheritance Functions
bool Sound::Is(std::string Type)
{
    return Type == "Sound";
}

void Sound::Render()
{

}

void Sound::Start()
{

}

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
