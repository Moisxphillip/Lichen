#ifndef LICHEN_TEXTURE
#define LICHEN_TEXTURE

#include <string>
#include "../../engine/lib/Vector2.hpp"


class Texture
{
    private:
        unsigned int _TextureID;
        std::string _Path;
        unsigned char* _LocalBuffer;
        int _Width, _Height, _BytesPerPixel;

    public:
        Texture(const std::string&);
        ~Texture();

        void Bind(unsigned int = 0);
        void Render();
        void Unbind();
        int GetWidth();
        int GetHeight();

};

#endif// LICHEN_TEXTURE