#ifndef LICHEN_TEXT
#define LICHEN_TEXT

#include "SDL2/SDL_ttf.h"

#include "Components/Component.hpp"
#include "Core/Enum.hpp"
#include "Graphics/FontHandler.hpp"
#include "Tools/Color.hpp"

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
        Text(GameObject& Parent, std::string FontPath, int FontSize, TextStyle Style, std::string TextLine, Color Colour);
        ~Text();

        void SetColor(Color Colour);
        void SetFontFile(std::string Path);
        void SetFontSize(int FontSize);
        void SetWrap(int PixelWidth);
        void SetStyle(TextStyle Style);
        void SetAlignment(TextAlignment Align);
        void SetText(std::string Text);
        void Render();
        void Render(Vector2 Position);
        void Update(float Dt);
};

#endif// LICHEN_TEXT