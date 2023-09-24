#include "Components/TileSet.hpp"
#include "Tools/Tools.hpp"

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
    _Set->SetRows(_Rows);
    _Set->SetColumns(_Columns);
    _MaxTiles = _Rows*_Columns;
    _Set->SetFrameCount(_MaxTiles);
}

TileSet::~TileSet()
{
    delete _TileObj;
    delete _Set;
}
void TileSet::RenderTile(int Index, float x, float y)
{
    if(Index <= 0)
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
