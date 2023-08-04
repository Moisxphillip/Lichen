#include "../lib/Text.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"
#include "../lib/Settings.hpp"

Text::Text(GameObject& GameObj, std::string Font, int Size, TextStyle Style, std::string Text, SDL_Color NewColor)
: Component(GameObj)
{
    _FontFile = Font;
    _Color = NewColor;
    _FontSize = Size;
    _Style = Style;
    _Text = Text;
    _Font = Resources::GetFont(_FontFile);
    _Texture = nullptr;
    _RemakeTexture();
}

Text::~Text()
{
    if(_Texture != nullptr)
    {
        SDL_DestroyTexture(_Texture);
        _Texture = nullptr;
    }
}

void Text::_RemakeTexture()
{
    if(TTF_SetFontSize(_Font, _FontSize) < 0)
    {
        Error("Text::_RemakeTexture: Could not set font size");
    }

    SDL_Surface* FontSurface;

    if(_Style == TextStyle::SOLID)
    {
        FontSurface = TTF_RenderText_Solid(_Font, _Text.c_str(), _Color);
    }
    else if(_Style == TextStyle::BLENDED)
    {
        FontSurface = TTF_RenderText_Blended(_Font, _Text.c_str(), _Color);
    }
    else if(_Style == TextStyle::SHADED)
    {
        SDL_Color Black = {0,0,0,0};
        FontSurface = TTF_RenderText_Shaded(_Font, _Text.c_str(), _Color, Black);
    }

    Parent.Box.Redimension(Vector2(FontSurface->w, FontSurface->h));
    _Texture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), FontSurface);
    
    if(_Texture == nullptr)
    {
        Error("Text::_RemakeTexture: Could not convert surface into texture");
    }

    SDL_FreeSurface(FontSurface);
}

void Text::SetColor(SDL_Color NewColor)
{
    _Color = NewColor;
    _RemakeTexture();
}

void Text::SetFontFile(std::string Font)
{
    _FontFile = Font;
    _Font = Resources::GetFont(_FontFile);
    _RemakeTexture();
}

void Text::SetFontSize(int Size)
{
    _FontSize = Size;
    _RemakeTexture();
}

void Text::SetStyle(TextStyle Style)
{
    _Style = Style;
    _RemakeTexture();
}

void Text::SetText(std::string Text)
{
    _Text = Text;
    _RemakeTexture();
}


bool Text::Is(std::string Type)
{
    return ("Text" == Type);
}

void Text::Render()
{
    if(_Texture != nullptr)
    {
        SDL_Rect Clip = {0,0, (int)Parent.Box.w, (int)Parent.Box.h};
        SDL_Rect Destiny = {(int)(Parent.Box.x - Engine::Instance().GetState().Cam.Position.x),
            (int)(Parent.Box.y - Engine::Instance().GetState().Cam.Position.y),
            (int)Parent.Box.w, (int)Parent.Box.h};
        if(SDL_RenderCopyEx(Engine::Instance().GetRenderer(), _Texture, &Clip, &Destiny, 
            Vector2::RadToDeg(Parent.Angle),nullptr, (SDL_RendererFlip) Flip::N))
        {
            Error("Text::Render: Could not render text");
        }
    }
}

void Text::Update(float Dt)
{

}
