#include "../lib/Image.hpp"
#include "../lib/Resources.hpp"
#include "../lib/Tools.hpp"
#include <algorithm>

//Review and fix later
// class TextureCarrousel
// {
// private:
//     static int _NextSlot;
//     static std::vector<unsigned int> _SlotID;
//     static void _Bind(unsigned int ID, int Slot);
// public:
//     static unsigned int GetAvaliableSlot(unsigned int ID);
// };

// std::vector<unsigned int> TextureCarrousel::_SlotID(0,16);
// int TextureCarrousel::_NextSlot = 0;

// unsigned int TextureCarrousel::GetAvaliableSlot(unsigned int ID)
// {
//     for (int i = 0; i < 16; i++)
//     {
//         if (_SlotID[i] == ID)
//         {
//             std::cout << _SlotID.size();
//             _Bind(ID, i);
//             return i;
//         }
//     }
//     _SlotID[_NextSlot] = ID;
//     _Bind(ID, _NextSlot);
//     int Slot = _NextSlot;
//     ++_NextSlot;
//     if (_NextSlot == 16)
//     {
//         _NextSlot %= 16;
//     }
//     return Slot;
// }

// void TextureCarrousel::_Bind(unsigned int ID, int Slot)
// {
//     glActiveTexture(GL_TEXTURE0 + Slot);
//     glBindTexture(GL_TEXTURE_2D, ID);
// }

Image::Image(const std::string& File):
_Index{0,1,2,2,3,0}
{
    _Texture = Resources::GetTexture(File);
    _Width = _Texture->GetWidth();
    _Height = _Texture->GetHeight();
        
    //vertex pos                                 | destiny rect
    _Square[0] = {(float)-1.0 * (_Width/2), 1.0f, (float)-1.0 * (_Height/2),      0, 1,};
    _Square[1] = {(float)1.0  * (_Width/2), 1.0f, (float)-1.0 * (_Height/2),      1, 1,};
    _Square[2] = {(float)1.0  * (_Width/2), 1.0f, (float) 1.0 * (_Height/2),      1, 0,};
    _Square[3] = {(float)-1.0 * (_Width/2), 1.0f, (float) 1.0 * (_Height/2),      0, 0};
    
    _Va = new VertexArray;
    _Vb = new VertexBuffer(_Square, 4*sizeof(VertexInfo), DrawMode::Dynamic);
    _Vbl = new VertexBufferLayout;
    _Vbl->Push(GL_FLOAT, 3); //Position data
    _Vbl->Push(GL_FLOAT, 2); //texture mapping data
    _Va->AddBuffer(*_Vb, *_Vbl);
    _Ib = new IndexBuffer(_Index, 6);

    _Shader = new Shader();
    _Shader->CreateShader();

    _LayerMode = DepthMode::Background;
    _ShaderUpdated = true;
    _LastDepth = -99999;
    _LastScale = Vector2(-99999, -99999);
    _LastPos = Vector2(-99999, -99999);
    _LastAngle = -99999;
    _LastDst = ___ImageRect{-99999, -99999,-99999, -99999};
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

Color Image::GetColor()
{
    return _NextColor;
}

void Image::Render(Renderer& RenderDevice, glm::mat4& Projection, Vector2 Position, Vector2 Scale, ___ImageRect Dst, float Angle, Flip CurrFlip, DepthMode Depth, int Layer)
{
    if(_LastPos != Position || _LastAngle != Angle)
    {
        _LastAngle=Angle;_LastPos=Position;
        // _Model = glm::translate(glm::mat4(1.0), glm::vec3(std::floor(Position.x),std::floor(Position.y), 0));//Reduces artifacts, can have some shaking tho
        _Model = glm::translate(glm::mat4(1.0), glm::vec3(Position.x,Position.y, 0));//Usual positioning
        _Model = glm::rotate(_Model,Angle, glm::vec3(0, 0, 1));
    }

    bool VbAltered = false;
    if (Scale != _LastScale )
    {
        _LastScale=Scale;
        //Calculate image size
        float X = (Dst.w/2) * (Scale.x), Y = (Dst.h/2) *(Scale.y);
        // float X = (Dst.w/2) * (Scale.x + 17e-3), Y = (Dst.h/2) *(Scale.y + 17e-3);//Deforms the tiles tho, find a better way to do this later
        _Square[0].x = -X; _Square[0].y = -Y;
        _Square[1].x =  X; _Square[1].y = -Y;
        _Square[2].x =  X; _Square[2].y =  Y;
        _Square[3].x = -X; _Square[3].y =  Y;
        VbAltered = true;
    }

    //3D layering disabled for now
    // if(_LayerMode!= Depth) //On depth mode switch, always make sure there's an update
    // {
    //     _LayerMode=Depth;
    //     _LastDepth = -999999;
    // }

    // if(_LayerMode == DepthMode::Dynamic && Layer != _LastDepth) //Checking an int is faster and enough for this. Also, layer = sprite y here
    // {
    //     //Normalize between min and max y height
    //     //
    //     _Square[0].z = (Position.y+_Height)/1000.0f;
    //     _Square[1].z = (Position.y+_Height)/1000.0f;
    //     _Square[2].z = (Position.y+_Height)/1000.0f;
    //     _Square[3].z = (Position.y+_Height)/1000.0f;
    //     VbAltered = true;
    // }
    // else if(Layer != _LastDepth) //Won't cause problems in case of depthmode change as the last depth is changed in the mode switch above
    // {
    //     //Please don't use numbers larger than 100 or negatives for layer indexes, there's no real need for that ;-;
    //     float Place = (_LayerMode == DepthMode::Background ? -1.0f+(float)Layer/100.0f : 40.0f+(float)Layer/100.0f);
    //     _Square[0].z = Place;
    //     _Square[1].z = Place;
    //     _Square[2].z = Place;
    //     _Square[3].z = Place;
    //     VbAltered = true;
    // }
    
    bool RectChanged = (Dst.x != _LastDst.x || Dst.y != _LastDst.y || Dst.w != _LastDst.w || Dst.h != _LastDst.h);

    if(RectChanged || _LastFlip != CurrFlip)
    {
        //Map texture positions on X and Y based on Dst rectangle
        _LastDst=Dst;_LastFlip=CurrFlip;
        float DstX0 = Clamp(CurrFlip == Flip::H || CurrFlip == Flip::HV ? (float)(Dst.x+Dst.w) / (float)_Width : (float)Dst.x / (float)_Width),
              DstX1 = Clamp(CurrFlip == Flip::H || CurrFlip == Flip::HV ? (float)Dst.x / (float)_Width : (float)(Dst.x+Dst.w) / (float)_Width);
        float DstY0 = Clamp(CurrFlip == Flip::V || CurrFlip == Flip::HV ? 1.0f-(float)Dst.y/(float)_Height : 1.0f-(float)(Dst.y+Dst.h)/(float)_Height),
              DstY1 = Clamp(CurrFlip == Flip::V || CurrFlip == Flip::HV ? 1.0f-(float)(Dst.y+Dst.h)/(float)_Height : 1.0f-(float)Dst.y/(float)_Height);

        _Square[0].dstx = DstX0; _Square[0].dsty = DstY1;
        _Square[1].dstx = DstX1; _Square[1].dsty = DstY1;
        _Square[2].dstx = DstX1; _Square[2].dsty = DstY0;
        _Square[3].dstx = DstX0; _Square[3].dsty = DstY0;
        VbAltered = true;
    }
    if (_ShaderUpdated)
    {
        VbAltered = true;
    }
    if(VbAltered)
    {
        _Vb->Bind(); //Update vertex data that has been altered
    }

    _Texture->Bind();
    _Shader->SetUniform1i("U_Texture", 0);
    if((_NextColor != _LastColor) || _ShaderUpdated)
    {
        _LastColor = _NextColor;
        _Shader->SetUniform4f("U_Color", _LastColor.r, _LastColor.g, _LastColor.b, _LastColor.a);
    }
    glm::mat4 MVP = Projection*RenderDevice.GetView()*_Model;
    _Shader->SetUniformMat4f("U_Mvp",MVP);
    
    _ShaderUpdated = false;
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

Shader& Image::GetShader()
{
    _ShaderUpdated = true;
    return *_Shader;
}