#ifndef LICHEN_TILESET
#define LICHEN_TILESET

#include "Components/Sprite.hpp"

class TileSet
{
    private:
        Sprite *_Set;
        GameObject *_TileObj;
        int _Rows;
        int _Columns;
        int _MaxTiles;
        int _TileWidth;
        int _TileHeight;

    public:
        TileSet(int Width, int Height, std::string Path);
        ~TileSet();
        void RenderTile(int Index, float PosX, float PosY);
        int GetTileWidth();
        int GetTileHeight();
};



#endif//LICHEN_TILESET