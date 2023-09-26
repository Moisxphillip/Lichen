#include "Graphics/FontHandler.hpp"
#include "Graphics/Texture.hpp"
#include "Tools/Tools.hpp"


FontHandler::FontHandler():
_Index{0,1,2,2,3,0}
{
    std::string Path = "none";
    _Texture = new Texture(Path, LoadTexture::AsText); //Not added to Resources as each texture may be unique and prone to sudden changes
    int _Width = _Texture->GetWidth(), _Height = _Texture->GetHeight();
        
    //vertex pos                                 | destiny rect
    _Square[0] = {(float)-1.0 * (_Width/2), 0.0f, (float)-1.0 * (_Height/2),      0, 1,};
    _Square[1] = {(float)1.0  * (_Width/2), 0.0f, (float)-1.0 * (_Height/2),      1, 1,};
    _Square[2] = {(float)1.0  * (_Width/2), 0.0f, (float) 1.0 * (_Height/2),      1, 0,};
    _Square[3] = {(float)-1.0 * (_Width/2), 0.0f, (float) 1.0 * (_Height/2),      0, 0};
    
    _Va = new VertexArray;
    _Vb = new VertexBuffer(_Square, 4*sizeof(VertexInfo), DrawMode::Dynamic);
    _Vbl = new VertexBufferLayout;
    _Vbl->Push(GL_FLOAT, 3); //Position data
    _Vbl->Push(GL_FLOAT, 2); //texture mapping data
    _Va->AddBuffer(*_Vb, *_Vbl);
    _Ib = new IndexBuffer(_Index, 6);

    _Shader = new Shader();
    _Shader->CreateShader();

    _LastScale = Vector2(-99999, -99999);
    _LastPos = Vector2(-99999, -99999);
    _LastAngle = -99999;
    _LastDst = Rectangle(-99999, -99999,-99999, -99999);
    _LastFlip = Flip::N;
    _LastColor = Color("#ffaafa");
}

FontHandler::~FontHandler()
{
    delete _Shader;
    delete _Ib;
    delete _Vbl;
    delete _Vb;
    delete _Va;
    delete _Texture;
}

void FontHandler::UpdateHandler(TTF_Font* CurrFont, std::string& CurrText, int FontSize, int Wrap, TextStyle Style, TextAlignment Align)
{

    if(TTF_SetFontSize(CurrFont, FontSize) < 0)
    {
        Error("FontHandler::UpdateHandler: Could not set font size");
    }
    TTF_SetFontWrappedAlign(CurrFont, Align);

    SDL_Color White{255,255,255}; //Font main color is changed through shader
    SDL_Color Black{0,0,0}; //Black shade on text
    SDL_Surface* FontSurface = nullptr;

    switch(Style)
    {
        case TextStyle::BLENDED:
            FontSurface = TTF_RenderUTF8_Blended_Wrapped(CurrFont, CurrText.c_str(), White, Wrap);
            break;
        case TextStyle::SOLID:
            FontSurface = TTF_RenderUTF8_Solid_Wrapped(CurrFont, CurrText.c_str(), White, Wrap);
            break;
        case TextStyle::SHADED:
            FontSurface = TTF_RenderUTF8_Shaded_Wrapped(CurrFont, CurrText.c_str(), White, Black, Wrap);
            break;
    }
    _Texture->UpdateTexture(FontSurface);
}

void FontHandler::CustomUpdate(SDL_Surface* Surf)
{
    _Texture->UpdateTexture(Surf);
}

int FontHandler::GetWidth()
{
    return _Texture->GetWidth();
}

int FontHandler::GetHeight()
{
    return _Texture->GetHeight();
}

void FontHandler::Render(Renderer& RenderDevice, glm::mat4& Projection, Vector2 Position, float Angle, Flip CurrFlip, Color CurrColor)
{
    Rectangle Dst(0.0f, 0.0f, _Texture->GetWidth(), _Texture->GetHeight());
    if(_LastPos != Position || _LastAngle != Angle)
    {
        _LastAngle=Angle;_LastPos=Position;

        _Model = glm::translate(glm::mat4(1.0), glm::vec3(Position.x,Position.y, 0));
        _Model = glm::rotate(_Model,Angle, glm::vec3(0, 0, 1));
    }

    glm::mat4 MVP = Projection*RenderDevice.GetView()*_Model;
    
    if (Dst != _LastDst || _LastFlip != CurrFlip)
    {
        _LastDst=Dst;_LastFlip=CurrFlip;

        //Calculate image size
        float X = (Dst.w/2), Y = (Dst.h/2);

        //Map texture positions on X and Y based on Dst rectangle 
        float DstX0 = (CurrFlip == Flip::H || CurrFlip == Flip::HV ? 1 : 0),
              DstX1 = (CurrFlip == Flip::H || CurrFlip == Flip::HV ? 0 : 1);
        float DstY0 = (CurrFlip == Flip::V || CurrFlip == Flip::HV ? 0 : 1),
              DstY1 = (CurrFlip == Flip::V || CurrFlip == Flip::HV ? 1 : 0);

        _Square[0] = {-1 * X,-1 * Y, 0.0f,        DstX0,   DstY1};
        _Square[1] = { 1 * X,-1 * Y, 0.0f,        DstX1,   DstY1};
        _Square[2] = { 1 * X, 1 * Y, 0.0f,        DstX1,   DstY0};
        _Square[3] = {-1 * X, 1 * Y, 0.0f,        DstX0,   DstY0};
        
        _Vb->Bind();
    }
    _Texture->Bind();
    _Shader->SetUniform1i("U_Texture", 0);
    
    if (CurrColor != _LastColor)
    {
        _LastColor = CurrColor;
    }
    _Shader->SetUniform4f("U_Color", CurrColor.r, CurrColor.g, CurrColor.b, CurrColor.a);
    _Shader->SetUniformMat4f("U_Mvp",MVP);

    RenderDevice.Draw(*_Va, *_Ib, *_Shader);
}