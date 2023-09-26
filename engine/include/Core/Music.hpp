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
        bool IsOpen();

};

#endif//LICHEN_MUSIC