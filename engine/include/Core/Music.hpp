#ifndef LICHEN_MUSIC
#define LICHEN_MUSIC

#include <string>
#include "SDL2/SDL_mixer.h"

class Music
{
    private:        
        Mix_Music* _Music;
        int _MusicVolume;

    public:
        Music(std::string Path);
        Music();
        ~Music();
        
        void Play(int Times = -1, int FadeIn = 0);
        void Stop(int FadeOut  = 1500);
        void Open(std::string Path);
        void SetVolume(int Volume = 255);
        bool IsOpen();
        bool IsPlaying();

};

#endif//LICHEN_MUSIC