#include "../lib/Image.hpp"
#include "../../engine/lib/Tools.hpp"


Image::Image(const std::string& File):
_Index{0,1,2,2,3,0}
{
    _Texture = new Texture(File);
    _Width = _Texture->GetWidth();
    _Height = _Texture->GetHeight();
        
    //vertex pos                                 | destiny rect
    _Square[0] = {(float)-1.0 * (_Width/2), (float)-1.0 * (_Height/2),      0, 1,};
    _Square[1] = {(float)1.0  * (_Width/2), (float)-1.0 * (_Height/2),      1, 1,};
    _Square[2] = {(float)1.0  * (_Width/2), (float) 1.0 * (_Height/2),      1, 0,};
    _Square[3] = {(float)-1.0 * (_Width/2), (float) 1.0 * (_Height/2),      0, 0};
    
    _Va = new VertexArray;
    _Vb = new VertexBuffer(_Square, 4*sizeof(VertexInfo));
    _Vbl = new VertexBufferLayout;
    _Vbl->Push(GL_FLOAT, 2); //Position data
    _Vbl->Push(GL_FLOAT, 2); //texture mapping data
    _Va->AddBuffer(*_Vb, *_Vbl);
    _Ib = new IndexBuffer(_Index, 6);

    _Shader = new Shader();
    _Shader->CreateShader("./game/shader/V.vert","./game/shader/F.frag");

    _LastScale = Vector2(-99999, -99999);
    _LastPos = Vector2(-99999, -99999);
    _LastAngle = -99999;
    _LastDst = Rect(-99999, -99999,-99999, -99999);
}

Image::~Image()
{
    delete _Shader;
    delete _Ib;
    delete _Vbl;
    delete _Vb;
    delete _Va;
    delete _Texture;
}

void Image::Render(Renderer& RenderDevice, glm::mat4& Projection, glm::mat4& View, Vector2 Position, Vector2 Scale, Rect Dst, float Angle)
{
    if(_LastPos != Position || _LastAngle != Angle)
    {
        _LastAngle=Angle;_LastPos=Position;

        _Model = glm::translate(glm::mat4(1.0), glm::vec3(Position.x,Position.y, 0));
        _Model = glm::rotate(_Model,Angle, glm::vec3(0, 0, 1));
    }

    glm::mat4 MVP = Projection*View*_Model;
    
    if (Scale != _LastScale || Dst != _LastDst)
    {
        _LastScale=Scale;_LastDst=Dst;
        //FIX formulas, crop and size settings are not working as intended!!!
        //Crop is stretching to total size and cutting on wrong y direction
        //Size won't change properly, meaning the future frames will probably just be stretched to fit the area
        _Square[0] = {-1 * (Dst.w/2) * Scale.x,-1 * (Dst.h/2) *Scale.y,         Dst.x/_Width,           1.0f-Dst.y/_Height};
        _Square[1] = { 1 * (Dst.w/2) * Scale.x,-1 * (Dst.h/2) *Scale.y,         (Dst.x+Dst.w)/_Width,   1.0f-Dst.y/_Height};
        _Square[2] = { 1 * (Dst.w/2) * Scale.x, 1 * (Dst.h/2) *Scale.y,         (Dst.x+Dst.w)/_Width,   1.0f-(Dst.y+Dst.h)/_Height};
        _Square[3] = {-1 * (Dst.w/2) * Scale.x, 1 * (Dst.h/2) *Scale.y,         Dst.x/_Width,           1.0f-(Dst.y+Dst.h)/_Height};

        // _Square[0] = {-1 * (Dst.w/2) * Scale.x,-1 * (Dst.h/2) *Scale.y,         Clamp(Dst.x/_Width),           Clamp(1.0f-Dst.y/_Height)};
        // _Square[1] = { 1 * (Dst.w/2) * Scale.x,-1 * (Dst.h/2) *Scale.y,         Clamp((Dst.x+Dst.w)/_Width),   Clamp(1.0f-Dst.y/_Height)};
        // _Square[2] = { 1 * (Dst.w/2) * Scale.x, 1 * (Dst.h/2) *Scale.y,         Clamp((Dst.x+Dst.w)/_Width),   Clamp(1.0f-(Dst.y+Dst.h)/_Height)};
        // _Square[3] = {-1 * (Dst.w/2) * Scale.x, 1 * (Dst.h/2) *Scale.y,         Clamp(Dst.x/_Width),           Clamp(1.0f-(Dst.y+Dst.h)/_Height)};
        _Vb->Bind();
    }
    _Texture->Bind();
    _Shader->SetUniform1i("U_Texture", 0);
    
    _Shader->SetUniform4f("U_Color", 1, 1, 1, 1.0);
    _Shader->SetUniformMat4f("U_Mvp",MVP);

    RenderDevice.Draw(*_Va, *_Ib, *_Shader);
}