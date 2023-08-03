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
    Index;
    if(Index == 0)
    {
        return;
    } 

    if (int(Index) >= _MaxTiles) //Just in case someone asks for tiles outside the boundaries
    {
        Error("TileSet::RenderTile: Tile requested exceded the max number of tiles on current Set");
    }
    Index--;
    //Gets the position of needed sprite section
    int ClipX = (Index%_Columns)* _TileWidth,
    ClipY = (Index/_Columns)*_TileHeight;

    //Sets the sprite area to be exhibited and renders it
    _Set->SetClip(ClipX, ClipY, _TileWidth, _TileHeight);
    _Set->Render(x,y);
    Index++;
}

int TileSet::GetTileWidth()
{
    return _TileWidth;
}

int TileSet::GetTileHeight()
{
    return _TileHeight;
}
