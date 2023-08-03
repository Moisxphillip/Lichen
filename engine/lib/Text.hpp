#ifndef LICHEN_TEXT
#define LICHEN_TEXT

#include "SDL2/SDL_ttf.h"

#include "Component.hpp"

class Text : public Component
{
    public:        
        enum TextStyle
        {
            SOLID,
            SHADED,
            BLENDED
        };

    private:
        TTF_Font* _Font;
        SDL_Texture* _Texture;
        std::string _Text;
        TextStyle _Style;
        std::string _FontFile;
        int _FontSize;
        SDL_Color _Color;
        
        void _RemakeTexture();

    public:
        Text(GameObject&, std::string, int, TextStyle, std::string, SDL_Color);
        ~Text();

        void SetColor(SDL_Color);
        void SetFontFile(std::string);
        void SetFontSize(int);
        void SetStyle(TextStyle);
        void SetText(std::string);

        bool Is(std::string);
        void Render();
        void Update(float);

};

#endif// LICHEN_TEXT