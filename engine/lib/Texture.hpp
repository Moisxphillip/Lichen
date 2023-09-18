#ifndef LICHEN_TEXTURE
#define LICHEN_TEXTURE

#include <string>

#include "SDL2/SDL_ttf.h"

#include "Vector2.hpp"
#include "Enum.hpp"
#include "Color.hpp"

class Texture
{
    private:
        unsigned int _TextureID;
        std::string _Path;
        int _Width, _Height, _BytesPerPixel;
        LoadTexture _LoadMode;
        void _SurfaceToTexture(SDL_Surface*);

    public:
        Texture(const std::string&, LoadTexture);
        ~Texture();

        void Bind(unsigned int = 0);
        void Unbind();
        void UpdateTexture(SDL_Surface*);
        unsigned int GetTextureID();
        int GetWidth();
        int GetHeight();

};

#endif// LICHEN_TEXTURE