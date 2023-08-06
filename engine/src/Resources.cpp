#include <algorithm>

#include "../lib/Resources.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Tools.hpp"

std::unordered_map<std::string, SDL_Texture*> Resources::_ImageTable;
std::unordered_map<std::string, Mix_Music*> Resources::_MusicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::_SoundTable;
std::unordered_map<std::string, TTF_Font*> Resources::_FontTable;

SDL_Texture* Resources::GetImage(std::string& File)
{
    if(!_ImageTable.count(File))
    {
        SDL_Texture* NewImage = IMG_LoadTexture(Engine::Instance().GetRenderer(), File.c_str());
        if(NewImage == nullptr)
        {
            Error("Resources::GetImage: Texture could not be loaded");
        }
        _ImageTable[File] = NewImage;
        return NewImage;
    }
    return _ImageTable[File];
}

Mix_Music* Resources::GetMusic(std::string& File)
{
    if(!_MusicTable.count(File))
    {
        Mix_Music* NewMusic = Mix_LoadMUS(File.c_str());
        if(NewMusic == nullptr)
        {
            Error("Resources::GetMusic: Music could not be loaded");
        }
        _MusicTable[File] = NewMusic;
        return NewMusic;
    }
    return _MusicTable[File];
}

Mix_Chunk* Resources::GetSound(std::string& File)
{
    if(!_SoundTable.count(File))
    {
        Mix_Chunk* NewSound = Mix_LoadWAV(File.c_str());
        if(NewSound == nullptr)
        {
            Error("Resources::GetSound: Chunk could not be loaded");
        }
        _SoundTable[File] = NewSound;
        return NewSound;
    }
    return _SoundTable[File];
}

TTF_Font* Resources::GetFont(std::string& File)
{
    if(!_FontTable.count(File))
    {
        TTF_Font* NewFont = TTF_OpenFont(File.c_str(), 12);
        if(NewFont == nullptr)
        {
            Error("Resources::GetFont: Font could not be loaded");
        }
        _FontTable[File] = NewFont;
        return NewFont;
    }
    return _FontTable[File];
}

void Resources::ClearImages()
{
    std::for_each(_ImageTable.begin(), _ImageTable.end(), //Iterates and use lambda for each case
    [](auto& it){SDL_DestroyTexture(it.second);});
    _ImageTable.clear();
}

void Resources::ClearMusics()
{
    std::for_each(_MusicTable.begin(), _MusicTable.end(), //Iterates and use lambda for each case
    [](auto& it){Mix_FreeMusic(it.second);});
    _MusicTable.clear();
}

void Resources::ClearSounds()
{
    std::for_each(_SoundTable.begin(), _SoundTable.end(), //Iterates and use lambda for each case
    [](auto& it){Mix_FreeChunk(it.second);}); 
    _SoundTable.clear();
}

void Resources::ClearFonts()
{
    std::for_each(_FontTable.begin(), _FontTable.end(), //Iterates and use lambda for each case
    [](auto& it){TTF_CloseFont(it.second);}); 
    _FontTable.clear();
}

void Resources::FlushContext()
{
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}
