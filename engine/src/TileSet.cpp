#include "../lib/TileSet.hpp"
#include "../lib/Tools.hpp"

TileSet::TileSet(int TileWidth, int TileHeight, std::string File)
{
    //Defines dimensions for current TileMap
    _TileWidth = TileWidth; 
    _TileHeight = TileHeight;

    //Make a GameObject to be associated to the Sprite
    _TileObj = new GameObject;
    _Set = new Sprite(*_TileObj, File);

    //Next step only happens if image opened correctly
    if(!_Set->IsOpen())
    {
        Error("TileSet::TileSet: TileSet reference image could not be opened correctly");
    }

    //Calculates the number of items on the tilemap based on total image dimensions/tile dimensions
    _Rows = _Set->GetHeight()/_TileHeight;
    _Columns = _Set->GetWidth()/_TileWidth;
    _MaxTiles = _Rows*_Columns;
}

TileSet::~TileSet()
{
    //Memory leaks are not cool
    delete _TileObj;
    delete _Set;
}

void TileSet::RenderTile(int Index, float x, float y)
{
    if(Index == 0)//For use with TileD maps, -1
    {
        return;
    } 
    Index-=1;
    _Set->SetFrame(Index);
    _Set->Render(x,y);
}

int TileSet::GetTileWidth()
{
    return _TileWidth;
}

int TileSet::GetTileHeight()
{
    return _TileHeight;
}
