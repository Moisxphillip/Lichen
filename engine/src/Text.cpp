#include "../lib/Text.hpp"
#include "../lib/Game.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"

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

    GameObjAssoc.Box.Redimension(Vector2(FontSurface->w, FontSurface->h));
    _Texture = SDL_CreateTextureFromSurface(Game::Instance().GetRenderer(), FontSurface);
    
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
        SDL_Rect Clip = {0,0, (int)GameObjAssoc.Box.w, (int)GameObjAssoc.Box.h};
        SDL_Rect Destiny = {(int)(GameObjAssoc.Box.x - Game::Instance().GetState().Cam.Position.x),
            (int)(GameObjAssoc.Box.y - Game::Instance().GetState().Cam.Position.y),
            (int)GameObjAssoc.Box.w, (int)GameObjAssoc.Box.h};
        if(SDL_RenderCopyEx(Game::Instance().GetRenderer(), _Texture, &Clip, &Destiny, 
            Vector2::RadToDeg(GameObjAssoc.Angle),nullptr, (SDL_RendererFlip) Flip::N))
        {
            Error("Text::Render: Could not render text");
        }
    }
}

void Text::Update(float Dt)
{

}
