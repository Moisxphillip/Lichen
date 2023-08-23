#ifndef LICHEN_IMAGE
#define LICHEN_IMAGE

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../../engine/lib/Vector2.hpp"
#include "../../engine/lib/Rect.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

struct VertexInfo
{
    float x, y, dstx, dsty;
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

        //State registering
        Vector2 _LastPos;
        Vector2 _LastScale;
        Rect _LastDst;
        float _LastAngle;

    public:
        Image(const std::string&);
        ~Image();
        void Render(Renderer&, glm::mat4&, glm::mat4&, Vector2, Vector2, Rect, float);



};
#endif//LICHEN_IMAGE