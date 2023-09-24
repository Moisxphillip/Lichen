#ifndef LICHEN_TEXTURE
#define LICHEN_TEXTURE

#include <string>

#include "SDL2/SDL_ttf.h"

#include "Math/Vector2.hpp"
#include "Core/Enum.hpp"
#include "Tools/Color.hpp"

class Texture
{
    private:
        unsigned int _TextureID;
        std::string _Path;
        int _Width, _Height, _BytesPerPixel;
        LoadTexture _LoadMode;
        void _SurfaceToTexture(SDL_Surface* Surface);

    public:
        Texture(const std::string& Path, LoadTexture Mode);
        ~Texture();

        void Bind(unsigned int ID = 0);
        void Unbind();
        void UpdateTexture(SDL_Surface* Surface);
        unsigned int GetTextureID();
        int GetWidth();
        int GetHeight();

};

#endif// LICHEN_TEXTURE