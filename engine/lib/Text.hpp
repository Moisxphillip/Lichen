#ifndef LICHEN_TEXT
#define LICHEN_TEXT

#include "SDL2/SDL_ttf.h"

#include "Component.hpp"
#include "Color.hpp"
#include "Enum.hpp"
#include "FontHandler.hpp"

class Text : public Component
{
    private:
        TTF_Font* _Font;
        FontHandler* _Handler;
        std::string _Text;
        std::string _FontFile;
        TextStyle _Style;
        Color _Color;
        int _FontSize;
        int _Wrap;
        TextAlignment _Align;
        
        void _RemakeTexture();

    public:
        Text(GameObject&, std::string, int, TextStyle, std::string, Color);
        ~Text();

        void SetColor(Color);
        void SetFontFile(std::string);
        void SetFontSize(int);
        void SetWrap(int);
        void SetStyle(TextStyle);
        void SetAlignment(TextAlignment);
        void SetText(std::string);

        void Render();
        void Update(float);

};

#endif// LICHEN_TEXT