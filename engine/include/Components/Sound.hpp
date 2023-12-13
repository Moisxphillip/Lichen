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
        static float _EarDistance;
        static float _LMinRadius;
        static float _LMaxRadius;
        static float _MinRadius;
        static float _MaxRadius;
    
    public:    
        bool Pan;
        bool Side;
        bool Linear;
        bool SelfDestruct;
        Sound(GameObject& Parent);
        Sound(GameObject& Parent, std::string Path);
        ~Sound();

        //Times 0: once
        void Play(int Times = 0, int FadeIn = 0);
        void Stop(int FadeOut = 0);
        void Open(std::string Path);
        bool IsOpen();
        bool IsPlaying();
        void SetVolume(int Volume = 255);
        
        //Inheritance Functions
        void Update(float Dt);

};

#endif//LICHEN_SOUND