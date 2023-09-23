#include "../lib/Text.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"

Text::Text(GameObject& GameObj, std::string Font, int Size, TextStyle Style, std::string Text, Color NewColor)
: Component(GameObj)
{
    _FontFile = Font;
    _Color = NewColor;
    _FontSize = Size;
    _Style = Style;
    _Text = Text;
    _Font = Resources::GetFont(_FontFile);
    _Handler = new FontHandler();
    _Wrap = 0;//break line on new line
    _Align = TextAlignment::LEFT; //Align text on the left
    _RemakeTexture();
    _Type = ComponentType::Text;
}

Text::~Text()
{
    if(_Handler != nullptr)
    {
        delete _Handler;
        _Handler = nullptr;
    }
}

void Text::_RemakeTexture()
{
   _Handler->UpdateHandler(_Font, _Text, _FontSize, _Wrap, _Style, _Align);
    Parent.Box.Redimension(Vector2(_Handler->GetWidth(), _Handler->GetHeight()));
}

void Text::SetColor(Color NewColor)
{
    _Color = NewColor;
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

void Text::SetWrap(int Wrap)
{
    _Wrap = Wrap;
    _RemakeTexture();
}

void Text::SetStyle(TextStyle Style)
{
    _Style = Style;
    _RemakeTexture();
}

void Text::SetAlignment(TextAlignment Align)
{
    _Align = Align;
    _RemakeTexture();
}

void Text::SetText(std::string Text)
{
    _Text = Text;
    _RemakeTexture();
}

void Text::Render()
{
    Vector2 Position = Parent.Box.Position();
    Position.x+=_Handler->GetWidth()/2.0f;
    Position.y+=_Handler->GetHeight()/2.0f;
    _Handler->Render(Engine::Instance().GetRenderer(),Engine::Instance().GetWindow().GetProjection(), Position, Parent.Angle, Flip::N, _Color);
}

void Text::Update(float Dt)//Add time flickering here
{
}
