#include "../lib/Image.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"


Image::Image(const std::string& File):
_Index{0,1,2,2,3,0}
{
    _Texture = Resources::GetTexture(File);
    _Width = _Texture->GetWidth();
    _Height = _Texture->GetHeight();
        
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
    _LastDst = Rect(-99999, -99999,-99999, -99999);
    _LastFlip = Flip::N;
    _LastColor =  Color("#FFF00FFF");//won't alter base color with shader at first
    _NextColor = Color("#FFFFFFFF");;
}

Image::~Image()
{
    delete _Shader;
    delete _Ib;
    delete _Vbl;
    delete _Vb;
    delete _Va;
}

void Image::SetColor(Color CurrColor)
{
    _NextColor = CurrColor;
}

void Image::Render(Renderer& RenderDevice, glm::mat4& Projection, Vector2 Position, Vector2 Scale, Rect Dst, float Angle, Flip CurrFlip)
{
    if(_LastPos != Position || _LastAngle != Angle)
    {
        _LastAngle=Angle;_LastPos=Position;

        _Model = glm::translate(glm::mat4(1.0), glm::vec3(Position.x,Position.y, 0));
        _Model = glm::rotate(_Model,Angle, glm::vec3(0, 0, 1));
    }

    _Texture->Bind();
    _Shader->SetUniform1i("U_Texture", 0);
    if(_NextColor != _LastColor)
    {
        _LastColor = _NextColor;
        _Shader->SetUniform4f("U_Color", _LastColor.r, _LastColor.g, _LastColor.b, _LastColor.a);
    }
    glm::mat4 MVP = Projection*RenderDevice.GetView()*_Model;
    _Shader->SetUniformMat4f("U_Mvp",MVP);
    
    if (Scale != _LastScale || !(Dst == _LastDst) || _LastFlip != CurrFlip)
    {
        _LastScale=Scale;_LastDst=Dst;_LastFlip=CurrFlip;

        //Calculate image size
        float X = (Dst.w/2) * Scale.x, Y = (Dst.h/2) *Scale.y;

        //Map texture positions on X and Y based on Dst rectangle
        float DstX0 = Clamp(CurrFlip == Flip::H || CurrFlip == Flip::HV ? (Dst.x+Dst.w)/_Width : Dst.x/_Width),
              DstX1 = Clamp(CurrFlip == Flip::H || CurrFlip == Flip::HV ? Dst.x/_Width : (Dst.x+Dst.w)/_Width);
        float DstY0 = Clamp(CurrFlip == Flip::V || CurrFlip == Flip::HV? 1.0f-Dst.y/_Height : 1.0f-(Dst.y+Dst.h)/_Height),
              DstY1 = Clamp(CurrFlip == Flip::V || CurrFlip == Flip::HV?1.0f-(Dst.y+Dst.h)/_Height : 1.0f-Dst.y/_Height);

        _Square[0] = {-1 * X,-1 * Y, 0.0f,        DstX0,   DstY1};
        _Square[1] = { 1 * X,-1 * Y, 0.0f,        DstX1,   DstY1};
        _Square[2] = { 1 * X, 1 * Y, 0.0f,        DstX1,   DstY0};
        _Square[3] = {-1 * X, 1 * Y, 0.0f,        DstX0,   DstY0};
        
        _Vb->Bind();
    }
    RenderDevice.Draw(*_Va, *_Ib, *_Shader);
}

int Image::GetWidth()
{
    return _Width;
}

int Image::GetHeight()
{
    return _Height;
}