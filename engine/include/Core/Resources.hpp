#ifndef LICHEN_RESOURCES
#define LICHEN_RESOURCES

#include <unordered_map>
#include <string>

//Library includes
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "Graphics/Texture.hpp"

class Resources
{
    private:
        static std::unordered_map<std::string, Texture*> _TextureTable;
        static std::unordered_map<std::string, SDL_Texture*> _ImageTable;
        static std::unordered_map<std::string, Mix_Music*> _MusicTable;
        static std::unordered_map<std::string, Mix_Chunk*> _SoundTable;
        static std::unordered_map<std::string, TTF_Font*> _FontTable;

    public:
        static Texture* GetTexture(const std::string& Path);
        static SDL_Texture* GetImage(std::string& Path);
        static Mix_Music* GetMusic(std::string& Path);
        static Mix_Chunk* GetSound(std::string& Path);
        static TTF_Font* GetFont(std::string& Path);

        static void ClearTextures();
        static void ClearImages();
        static void ClearMusics();
        static void ClearSounds();
        static void ClearFonts();
        static void FlushContext();
    
};

#endif//LICHEN_RESOURCES