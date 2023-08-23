#include "../lib/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"


Texture::Texture(const std::string& Path)
{
    _TextureID = 0;
    _Path = Path;
    _LocalBuffer = nullptr;
    _Width = 0;
    _Height = 0;
    _BytesPerPixel = 0;

    stbi_set_flip_vertically_on_load(1);//Puts texture upside down for OpenGL
    _LocalBuffer = stbi_load(Path.c_str(), &_Width, &_Height,&_BytesPerPixel, 4);

    glGenTextures(1, &_TextureID);
    glBindTexture(GL_TEXTURE_2D, _TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(_LocalBuffer != nullptr)
    {
        stbi_image_free(_LocalBuffer);
    }
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

int Texture::GetWidth()
{
    return _Width;
}

int Texture::GetHeight()
{
    return _Height;
}

void Texture::Render()
{
    
}