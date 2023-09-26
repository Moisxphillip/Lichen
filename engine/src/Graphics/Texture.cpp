#include "Graphics/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "SDL2/sdl_image.h"
#include "SDL2/sdl_ttf.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/Renderer.hpp"
#include "Tools/Tools.hpp"

Texture::Texture(const std::string& Path, LoadTexture Mode)
{
    _TextureID = 0;
    _Path = Path;
    _Width = 0;
    _Height = 0;
    _BytesPerPixel = 0;
    _LoadMode = Mode;

    if(Mode == LoadTexture::AsImage)
    { 
        unsigned char* _LocalBuffer;
        stbi_set_flip_vertically_on_load(1);//Puts texture upside down for OpenGL
        _LocalBuffer = stbi_load(Path.c_str(), &_Width, &_Height,&_BytesPerPixel, 4);

        glGenTextures(1, &_TextureID);
        glBindTexture(GL_TEXTURE_2D, _TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_LINEAR Causes some artifacts in the tiles borders
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//Can be clamped with GL_CLAMP_TO_EDGE
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if(_LocalBuffer != nullptr)
        {
            stbi_image_free(_LocalBuffer);
            _LocalBuffer = nullptr;
        }
    }
    else if(Mode == LoadTexture::AsText)
    {
        SDL_Surface* Surface, *Fixed;
        Surface = SDL_CreateRGBSurface(0,100,100,32,0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        SDL_FillRect(Surface, 0, Color("#000000").ColorUint32());
        _SurfaceToTexture(Surface);
    }
}

void Texture::_SurfaceToTexture(SDL_Surface* Surface)
{
    SDL_Surface* ConvertedSurface = SDL_ConvertSurfaceFormat(Surface, SDL_PIXELFORMAT_ABGR8888, 0);//Endianness problems may occur around here
    if (!ConvertedSurface)
    {
        Error("Texture::_SurfaceToTexture: Conversion failed");
        SDL_FreeSurface(Surface);
        return;
    }
    SDL_FreeSurface(Surface);
    
    glGenTextures(1, &_TextureID);
    glBindTexture(GL_TEXTURE_2D, _TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
    _Width = ConvertedSurface->w;
    _Height= ConvertedSurface->h;
    _BytesPerPixel = ConvertedSurface->format->BytesPerPixel;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ConvertedSurface->pixels);
    SDL_FreeSurface(ConvertedSurface);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_TextureID);
}

void Texture::Bind(unsigned int Slot)
{
    glActiveTexture(GL_TEXTURE0+Slot);
    glBindTexture(GL_TEXTURE_2D, _TextureID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::UpdateTexture(SDL_Surface* FontSurface)
{
    if(_LoadMode != LoadTexture::AsImage)
    {
        glDeleteTextures(1, &_TextureID);
        _SurfaceToTexture(FontSurface);
    }
}

unsigned int Texture::GetTextureID()
{
    return _TextureID;
}

int Texture::GetWidth()
{
    return _Width;
}

int Texture::GetHeight()
{
    return _Height;
}