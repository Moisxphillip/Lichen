#ifndef LICHEN_IMAGE
#define LICHEN_IMAGE

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Math/Vector2.hpp"
#include "Math/Rectangle.hpp"
#include "Core/Renderer.hpp"
#include "Core/Enum.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"

struct VertexInfo
{
    float x, y, z, dstx, dsty;
};

class Image
{
    private:
        int _Width, _Height;
        VertexInfo _Square[4];
        unsigned int _Index[6];
        Texture* _Texture;
        glm::mat4 _Model;
        VertexArray* _Va;
        VertexBuffer* _Vb;
        VertexBufferLayout* _Vbl;
        IndexBuffer* _Ib;
        Shader* _Shader;
        DepthMode _LayerMode;
        bool _ShaderUpdated;

        //State registering
        Vector2 _LastPos;
        Vector2 _LastScale;
        ___ImageRect _LastDst;
        float _LastAngle;
        int _LastDepth;
        Flip _LastFlip;
        Color _LastColor, _NextColor;

    public:
        Image(const std::string& Path);
        ~Image();
        void SetColor(Color Colour);
        Color GetColor();
        void Render(Renderer& Rend, glm::mat4& Projection, Vector2 Position, Vector2 Scale, ___ImageRect Rect, float Angle=0, Flip F=Flip::N, DepthMode Depth=DepthMode::Background, int Layer=0);
        int GetWidth();
        int GetHeight();
        Shader& GetShader();
};
#endif//LICHEN_IMAGE