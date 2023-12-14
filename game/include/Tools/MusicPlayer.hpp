#ifndef GAMEMUS
#define GAMEMUS

#include "Components/Component.hpp"
#include "Core/Music.hpp"
#include <queue>

class MusicPlayer : public Component
{
    private:
        std::queue<Music*> _Playlist;
        bool _Changing;
    public:
        static MusicPlayer* Self;
        MusicPlayer(GameObject& Parent);
        ~MusicPlayer();
        void Update(float Dt);
        void PlaceSong(const std::string& Path);
};

#endif//GAMEMUS