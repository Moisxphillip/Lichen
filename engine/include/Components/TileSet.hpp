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
        TileSet(int, int, std::string);
        ~TileSet();
        void RenderTile(int, float, float);
        int GetTileWidth();
        int GetTileHeight();
    
};



#endif//LICHEN_TILESET