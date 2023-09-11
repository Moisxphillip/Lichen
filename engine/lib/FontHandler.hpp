#ifndef LICHEN_FONTHANDLER
#define LICHEN_FONTHANDLER

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Vector2.hpp"
#include "Rectangle.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Enum.hpp"
#include "Image.hpp"

#include "SDL2/SDL_ttf.h"


class FontHandler
{
    private:
        VertexInfo _Square[4];
        unsigned int _Index[6];
        glm::mat4 _Model;

        Texture* _Texture;
        VertexArray* _Va;
        VertexBuffer* _Vb;
        VertexBufferLayout* _Vbl;
        IndexBuffer* _Ib;
        Shader* _Shader;
        
        //State registering
        Vector2 _LastPos;
        Vector2 _LastScale;
        Rectangle _LastDst;
        float _LastAngle;
        Flip _LastFlip;
        Color _LastColor;

    public:
        FontHandler();
        ~FontHandler();
        int GetWidth();
        int GetHeight();
        void UpdateHandler(TTF_Font*, std::string&, int, int, TextStyle, TextAlignment);
        void CustomUpdate(SDL_Surface*);
        void Render(Renderer&, glm::mat4&, Vector2, float, Flip , Color=Color("#FFFFFFFF"));



};
#endif//LICHEN_FONTHANDLER