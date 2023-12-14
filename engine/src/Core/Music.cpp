#include "Core/Music.hpp"
#include "Core/Resources.hpp"
#include "Tools/Tools.hpp"

Music::Music()
{
    _Music = nullptr;
    _MusicVolume = 255;
}

Music::Music(std::string File)
{
    _Music = nullptr;
    _MusicVolume = 255;
    Open(File);
}

Music::~Music()
{
}

//-1 = infinite loop
void Music::Play(int Times, int FadeIn)
{
    if(_Music == nullptr)
    {
        Error("Music::Play: Music asset not loaded");
        return;
    }

    if(Mix_FadeInMusic(_Music, Times, FadeIn))
    {
        Error("Music::Play: Music device failed to fade in and play");
    }
    Mix_VolumeMusic(_MusicVolume/2);
}

void Music::Stop(int FadeOut)
{
    if(!Mix_FadeOutMusic(FadeOut))
    {
        Error("Music::Stop: Fadeout Could not be scheduled");
    }
}

void Music::SetVolume(int Volume)
{
    _MusicVolume = Volume;
    Mix_VolumeMusic(Volume/2);
}

void Music::Open(std::string File)
{
    _Music = Resources::GetMusic(File);
    if(_Music == nullptr)
    {
        Error("Music::Open: Music asset could not be loaded");
    }
}

bool Music::IsOpen()
{
    return (_Music != nullptr);
}

bool Music::IsPlaying()
{
    return (Mix_PlayingMusic() != 0);
}
