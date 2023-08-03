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
        Music();
        Music(std::string);
        ~Music();
        
        void Play(int, int);
        void Stop(int);
        void Open(std::string);
        bool IsOpen();

};

#endif//LICHEN_MUSIC