#ifndef LICHEN_SOUND
#define LICHEN_SOUND

#include "SDL2/SDL_mixer.h"

#include "Component.hpp"

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
        Sound(GameObject&);
        Sound(GameObject&, std::string);
        ~Sound();

        void Play(int);
        void Stop();
        void Volume(int);
        void Open(std::string);
        bool IsOpen();
        bool IsPlaying();
        
        //Inheritance Functions
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);

};

#endif//LICHEN_SOUND