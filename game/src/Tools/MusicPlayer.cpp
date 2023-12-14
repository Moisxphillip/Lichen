#include "Tools/MusicPlayer.hpp"

MusicPlayer* MusicPlayer::Self = nullptr;

MusicPlayer::MusicPlayer(GameObject& Parent)
: Component(Parent)
{
    Self = this;
    _Changing = false;
}

MusicPlayer::~MusicPlayer()
{
    while(_Playlist.size() > 0)
    {   
        if(_Playlist.front()->IsPlaying())
        {
            _Playlist.front()->Stop(0);
        }
        delete _Playlist.front();
        _Playlist.pop();
    }
    Self = nullptr;
}

void MusicPlayer::Update(float Dt)
{
    if(_Playlist.size() < 1)
    {
        return;
    }

    if(_Playlist.size() > 1 && !_Changing)
    {
        _Changing = true;
        _Playlist.front()->Stop(1000);
    }

    if(_Changing && !_Playlist.front()->IsPlaying())
    {
        while(_Playlist.size() > 1)
        {
            delete _Playlist.front();
            _Playlist.pop();
        }
        _Playlist.front()->SetVolume(20);
        _Playlist.front()->Play(1000);
        _Changing = false;
    }

}

void MusicPlayer::PlaceSong(const std::string& Path)
{
    Music* Msc = new Music(Path);
    _Playlist.push(Msc);    
    if(_Playlist.size() == 1)
    {
        _Changing = true;
    }
}

