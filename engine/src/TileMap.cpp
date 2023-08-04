#include <fstream>

#include "../lib/TileMap.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Tools.hpp"
#include "../lib/Settings.hpp"

TileMap::TileMap(GameObject& GameObj, std::string File, TileSet* CurrTileSet)
: Component(GameObj)
{
    _CurrTileSet = nullptr;
    this->Load(File);
    this->SetTileSet(CurrTileSet);
    this->_RefLayer = 0;
    _RefLayerTurn = true;
    
}

void TileMap::SetRefLayer(int Value)
{
    _RefLayer = Value;
}

float TileMap::_GetLayerMult(int CurrLayer)
{
    CurrLayer-=_RefLayer;
    if(CurrLayer < 0)
    {
        CurrLayer--;
        return 1.0f/(CurrLayer);
    }

    //CurrLayer++;
    return (1.0f*CurrLayer); 
}

TileMap::~TileMap()
{

}

void TileMap::Load(std::string File)
{
    std::ifstream TextMap(File);
    if(!TextMap.is_open())
    {
        Error("TileMap::Load: File could not be opened");
        return;
    }
    std::string Entry;//Will collect the inputs for interpretation and storage
    
    //gets initial info about the map file
    std::getline(TextMap, Entry, ',');
    _MapWidth = stoi(Entry);
    std::getline(TextMap, Entry, ',');
    _MapHeight = stoi(Entry);
    std::getline(TextMap, Entry, ',');
    _MapDepth = stoi(Entry);
    
    _LayerArea = _MapHeight*_MapWidth;
    int TotalSize = _LayerArea*_MapDepth;

    _TileMatrix.reserve(TotalSize);//reserving beforehand to avoid losing performance with memory resizing
    for(int i = 0; i<TotalSize; i++)//gets sprite indexes for all layers
    {
        std::getline(TextMap, File, ',');
        _TileMatrix.push_back(stoi(File));
    }

    TextMap.close();
}

void TileMap::SetTileSet(TileSet* ToBeSet)
{
    if(ToBeSet == nullptr)
    {
        Error("TileMap::SetTileSet: New TileSet is null");
    }
    else if(_CurrTileSet != nullptr)
    {
        delete _CurrTileSet;
        _CurrTileSet = nullptr;
    }

    _CurrTileSet = ToBeSet;
}

int& TileMap::At(int x, int y, int z = 0)
{
    return _TileMatrix[(x + _MapWidth*y)+ _LayerArea*z];
}

void TileMap::RenderLayer(int Layer, int CamX, int CamY)
{
    float Parallax = _GetLayerMult(Layer);
    
    /* render formula is not properly working with layers below base, must fix 
    -- boundaries. For now, keep the variables as they worked before intervention.
    */
    int StartX = 0,
    StartY = 0;
   
    //Render until most far tile inside view
    int EndX = _MapWidth,
    EndY = _MapHeight;

    Vector2 Dimensions = Engine::Instance().GetRenderSize();
    Rect CamArea(0,0,(int)Dimensions.x, (int)Dimensions.y); 
    CamArea+= Engine::Instance().GetState().Cam.Position;

    for(int y = StartY; y < EndY; y++)//iterates through rows
    {
        for(int x = StartX; x < EndX; x++)//iterates through columns
        {
            float XPos = float(CamX*Parallax + x*_CurrTileSet->GetTileWidth());
            float YPos = float(CamY*Parallax + y*_CurrTileSet->GetTileHeight());

            if(CamArea.Contains(Vector2(XPos, YPos)) || CamArea.Contains(Vector2(XPos+_CurrTileSet->GetTileWidth(), YPos))
                || CamArea.Contains(Vector2(XPos, YPos+_CurrTileSet->GetTileHeight())) || CamArea.Contains(Vector2(XPos+_CurrTileSet->GetTileWidth(), YPos+_CurrTileSet->GetTileHeight())))
            {
                _CurrTileSet->RenderTile(At(x, y, Layer), XPos, YPos);//finds tile identifier and render in position
            }
        }        
    }
}

int TileMap::GetWidth()
{
    return _MapWidth;
}

int TileMap::GetHeight()
{
    return _MapHeight;
}

int TileMap::GetDepth()
{
    return _MapDepth;
}

bool TileMap::Is(std::string Type)
{
    return (Type == "TileMap");
}

void TileMap::Render()
{
    if(_RefLayerTurn)
    {
        for(int l = 0; l <= _RefLayer; l++)//Renders each layer separately
        {
            RenderLayer(l, -Engine::Instance().GetState().Cam.Position.x, -Engine::Instance().GetState().Cam.Position.y);//Following specification hint
        }
    }
    else if(_RefLayer+1 != _MapDepth)
    {
        for(int l = _RefLayer+1; l < _MapDepth; l++)//Renders each layer separately
        {
            RenderLayer(l, -Engine::Instance().GetState().Cam.Position.x, -Engine::Instance().GetState().Cam.Position.y);//Following specification hint
        }
    }
    _RefLayerTurn = !_RefLayerTurn;//Changes next render turn
}

void TileMap::Start()
{

}

void TileMap::Update(float Dt)
{
}
