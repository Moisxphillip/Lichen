#ifndef LICHEN_SOUND
#define LICHEN_SOUND

#include "SDL2/SDL_mixer.h"

#include "Components/Component.hpp"

class Sound : public Component
{
    private:    
        Mix_Chunk* _SoundChunk;
        int _SoundChannel;
        int _SoundVolume;
        void _SoundPosition();
    
    public:    
        bool Pan;
        bool SelfDestruct;
        Sound(GameObject& Parent);
        Sound(GameObject& Parent, std::string Path);
        ~Sound();

        void Play(int Times = 0);
        void Stop();
        void Volume(int Value);
        void Open(std::string Path);
        bool IsOpen();
        bool IsPlaying();
        
        //Inheritance Functions
        void Update(float Dt);

};

#endif//LICHEN_SOUND