#ifndef GAME_LOOPSPRITE
#define GAME_LOOPSPRITE

#include <string>

#include "Components/Sprite.hpp"

class LoopSprite : public Component
{
    private:
        Sprite* _Sprite;
    public:
        Vector2 PixelsPerSecond;
        LoopSprite(GameObject& Parent, std::string File);
        ~LoopSprite();
        Sprite& GetSprite();
        void SetAnimationData(int Rows, int Columns, int Frames, float FrameTime);
        void Update(float Dt);
        void Render();
};

#endif//GAME_LOOPSPRITE