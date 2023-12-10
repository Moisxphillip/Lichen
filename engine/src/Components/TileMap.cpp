#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include "Components/TileMap.hpp"
#include "Components/AARectangle.hpp"
#include "Core/GameObject.hpp"
#include "Core/Engine.hpp"
#include "Tools/Tools.hpp"

TileMap::TileMap(GameObject& GameObj, std::string File, TileSet* CurrTileSet, bool LoadAsLegacy, bool IsZeroEmpty)
: Component(GameObj)
{
    _CurrTileSet = nullptr;
    IsZeroEmpty ? _LowerMarker=0 : _LowerMarker=1;
    if(LoadAsLegacy)
    {
        this->Load(File);
    }
    else
    {
        this->LoadCSV(File);
    }
    this->SetTileSet(CurrTileSet);

    _Type = ComponentType::TileMap;
    _Parallax = 1;
    Enabled = true;
}

TileMap::~TileMap()
{
    delete _CurrTileSet;
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

    std::vector<std::vector<int>> Map(_MapHeight, std::vector<int>(_MapWidth));
    for(int i = 0; i<_MapHeight; i++)//Reads file to vector of vectors
    {
        for(int j = 0; j<_MapWidth; j++)
        {
            std::getline(TextMap, Entry, ',');
            Map[i][j] = (stoi(Entry)+_LowerMarker);
        }
    }
    TextMap.close();
    _TileMatrix = Map;
}

void TileMap::LoadCSV(std::string File)
{
    std::ifstream TextMap(File+".csv");
    if(!TextMap.is_open())
    {
        Error("TileMap::LoadCSV: File could not be opened");
        return;
    }
    std::string Entry;//Will collect the inputs for interpretation and storage
    std::vector<std::vector<int>> Map;
    while(!TextMap.eof()) 
    {
        std::getline(TextMap, Entry, '\n');
        std::stringstream Line(Entry);
        std::vector<int> LineVec;
        for (int i; Line >> i;) 
        {
            LineVec.push_back(i);    
            if (Line.peek() == ',' or Line.peek() == '\n') 
            {
                Line.ignore();
            }
        }
        if (TextMap.eof()) 
        {
            break;
        }
        Map.emplace_back(LineVec);
    }
    _MapWidth = (int) Map[0].size();
    _MapHeight = (int) Map.size();
    TextMap.close();
    _TileMatrix = Map;
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

int TileMap::GetWidth()
{
    return _MapWidth;
}

int TileMap::GetHeight()
{
    return _MapHeight;
}

void TileMap::SetParallax(float New)
{
    _Parallax = New;
}

float TileMap::GetParallax()
{
    return _Parallax;
}

void TileMap::Render()
{
    if(!Enabled)
    {
        return;
    }

    int MinX = int(Camera::Position().x)/_CurrTileSet->GetTileWidth();
    int MinY = int(Camera::Position().y)/_CurrTileSet->GetTileHeight();
    
    int MaxX = (int(Camera::Position().x)%_CurrTileSet->GetTileWidth() + Engine::Instance().GetWindow().GetProjectionWidth()) /_CurrTileSet->GetTileWidth() +1;
    int MaxY = (int(Camera::Position().y)%_CurrTileSet->GetTileHeight()+ Engine::Instance().GetWindow().GetProjectionHeight())/_CurrTileSet->GetTileHeight()+1;

    // MinX*=_CurrTileSet->GetTileWidth();
    // MinY*=_CurrTileSet->GetTileHeight();

    MinX = std::min(std::max(MinX, 0), _MapWidth);
    MinY = std::min(std::max(MinY, 0), _MapHeight);
    for(int i = MinX; i < std::min(MinX+MaxX, _MapWidth); i++)
    {
        for(int j = MinY; j < std::min(MinY+MaxY, _MapHeight); j++)
        {
            
            // _Sprite->Render(MinX+_Sprite->GetWidth()*i, MinY + _Sprite->GetHeight()*j);
            _CurrTileSet->RenderTile(
                _TileMatrix[j][i],
                (float)(Parent.Box.x+i)*_CurrTileSet->GetTileWidth(),
                (float)(Parent.Box.y+j)*_CurrTileSet->GetTileHeight()
            );
            //Warning: Parallax not in use for the current game.
        }
    }



    //Old optimization, not so good
    // Vector2 Lower = Camera::Position()*_Parallax;
    // Vector2 Upper = (Lower + Engine::Instance().GetRenderSize())*_Parallax;
    // int Lx = floor(Lower.x)/_CurrTileSet->GetTileWidth()-4;//0;//
    // int Hx = floor(Upper.x)/_CurrTileSet->GetTileWidth()+4;//MapWidth;//
    // int Ly = floor(Lower.y)/_CurrTileSet->GetTileHeight()-4;//0;//
    // int Hy = floor(Upper.y)/_CurrTileSet->GetTileHeight()+4;//MapHeight;//

    // for (int y = std::max(Ly, 0); y < std::min(Hy, _MapHeight); y++)
    // {
    //     for (int x = std::max(Lx, 0); x < std::min(Hx, _MapWidth); x++) 
    //     {
    //         _CurrTileSet->RenderTile(
    //             _TileMatrix[y][x],
    //             (float)(Parent.Box.x+x)*_CurrTileSet->GetTileWidth()-((_Parallax-1)*(int)Lower.x),
    //             (float)(Parent.Box.y+y)*_CurrTileSet->GetTileHeight()-((_Parallax-1)*(int)Lower.y)
    //         );
    //     }
    // }
}

//__________________________________
// TileMap auto-collision generation/optimization code below.
// Abandon all hope before attempting to read it. Good luck.
//__________________________________

int TileMap::_Hash(std::vector<std::vector<int>>& Map) 
{
    int Hash, x;
    for(int i = 0; i < (int)Map.size(); i++) 
    {
        for(int j = 0; j < (int)Map[i].size(); j++) 
        {
            x = Map[i][j];
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = ((x >> 16) ^ x) * 0x45d9f3b;
            x = (x >> 16) ^ x;
            Hash ^= x + 0x9e3779b9 + (Hash << 6) + (Hash >> 2);
        }
    }
    return Hash;
}

bool TileMap::_HasMapChanged(int HashResult, std::string HashPath) 
{
    std::ifstream HashFile(HashPath);
    if(HashFile) 
    {
        std::string Entry;
        std::getline(HashFile, Entry,',');
        int x = stoi(Entry);
        if(x == HashResult) 
        {
            return false;
        }
        return true;    
    }
    return true;
}

std::vector<RectInt> TileMap::_LoadCoord(std::string File) 
{
    std::ifstream BoxCoords(File);
    if(!BoxCoords.is_open())
    {
        std::vector<RectInt> fail;
        return fail;
    }
    std::string Entry;
    int x;
    std::getline(BoxCoords, Entry, ',');
    x = stoi(Entry);
    std::vector<RectInt> Box(x);

    for(int i = 0; i<x; i++)
    {
        std::getline(BoxCoords, Entry, ',');
        Box[i].x = (stoi(Entry));
        std::getline(BoxCoords, Entry, ',');
        Box[i].y = (stoi(Entry));
        std::getline(BoxCoords, Entry, ',');
        Box[i].w = (stoi(Entry));
        std::getline(BoxCoords, Entry, ',');
        Box[i].h = (stoi(Entry));
    }
    BoxCoords.close();
    return Box;
}

void TileMap::_DumpCoord(const std::vector<RectInt>& Data, std::string File) 
{
    std::ofstream Output(File);
    Output << Data.size()<< ",\n";
    for(int i = 0; i<(int)Data.size(); i++) 
    {
        Output << Data[i].x <<','<< Data[i].y <<','<< Data[i].w <<','<< Data[i].h <<",\n";
    }
    Output.close();
}

void TileMap::_BorderMarking(std::vector<std::vector<int>> &Map) 
{
    int Index = 1;
    for(int i = 0; i < (int)Map.size(); i++) 
    {
        for(int j = 0; j < (int)Map[i].size(); j++) 
        {
            if(Map[i][j] > 0) 
            {
                if((j > 0 and Map[i][j-1] == -1 || Map[i][j-1] != -2)
                or (j < (int)Map[i].size()-1 and Map[i][j+1] == -1 || Map[i][j+1] != -2)
                or (i > 0 and Map[i-1][j] == -1 || Map[i-1][j] != -2)
                or (i < (int)Map.size()-1 and Map[i+1][j] == -1 || Map[i+1][j] != -2))
                {
                    Map[i][j] = Index;
                    Index++;
                } 
                else 
                {
                    Map[i][j] = -2;
                }
            }
        }
        Index++;
    }
}

void TileMap::_FindX(std::vector<std::vector<int>>& Map) 
{
    int Index = 1;
    for(int i = 0; i < (int)Map.size(); i++) 
    {
        for(int j = 0; j < (int)Map[i].size(); j++) 
        {
            if(Map[i][j] > 0)
            {
                Map[i][j] = Index;
                if(Map[i][j+1] > 0)
                {
                   Map[i][j+1] = Map[i][j];
                } 
                else 
                {
                    Index++;
                }
            }
        }
        Index++;
    }
}

std::vector<RectInt> TileMap::_MapToCoord(std::vector<std::vector<int>>& Map) 
{
    std::vector<RectInt> Coords;
    for(int i = 0; i < (int)Map.size(); i++)
    {
        for(int j = 0; j < (int)Map[i].size(); j++)
        {
            if(Map[i][j] > 0)
            {
                RectInt Res{j,i,1,1};
                if(Map[i][j] == Map[i][j+1])
                {
                    while(j < (int)Map[i].size()-2 and Map[i][j] == Map[i][j+1])
                    {
                        Res.w++;
                        j++;
                    }
                }
                Coords.emplace_back(Res);
            }
        }
    }
    return Coords;
}

void TileMap::_CoordOptimizer(std::vector<RectInt>& Coords) 
{
    std::sort(Coords.begin(), Coords.end(), 
        [](RectInt& a, RectInt& b){if(a.x == b.x) {return a.y < b.y;}return a.x < b.x;});

    for(int i = 0; i < (int)Coords.size(); i++) 
    {
        if(Coords[i].x == Coords[i+1].x
        and Coords[i].w == Coords[i+1].w
        and Coords[i].y == Coords[i+1].y - Coords[i].h) 
        {
            Coords[i].h++;
            Coords.erase(Coords.begin()+(i+1));
            i--;
        }
    }
}

#include "Tools/DistanceTrigger.hpp"
void TileMap::LoadCollision(std::string fileName)
{    
    int HashResult = _Hash(_TileMatrix);
    std::vector<RectInt> Block = _LoadCoord(fileName+"-rect.txt");
    bool RectAbsent = Block.size()==0;

    if(_HasMapChanged(HashResult, fileName+"-hash.txt") or RectAbsent) 
    {
        std::ofstream Output(fileName+"-hash.txt");//Register new hash
        Output << HashResult<< ",\n";
        Output.close();

        std::vector<std::vector<int>> Map = _TileMatrix;
        _BorderMarking(Map);
        _FindX(Map);
        Block = _MapToCoord(Map);
        _CoordOptimizer(Block);
        _DumpCoord(Block, fileName+"-rect.txt");
    }

    for(int i = 0; i < (int)Block.size(); i++) 
    {
        GameObject *ColliderObj = new GameObject(Parent.GetLayer());
        ColliderObj->Depth = Parent.Depth;
        AARectangle *TileCollider = new AARectangle(*ColliderObj, ColliderKind::Stationary, Rectangle(Block[i].x*_CurrTileSet->GetTileWidth(), Block[i].y*_CurrTileSet->GetTileHeight(),
            Block[i].w*_CurrTileSet->GetTileWidth(), Block[i].h*_CurrTileSet->GetTileHeight()));
        ColliderObj->AddComponent(new DistanceTrigger(*ColliderObj, TileCollider, 1000));
        ColliderObj->AddComponent(TileCollider);
        ColliderObj->Represents = CollisionMask::Terrain;
        ColliderObj->Box = Rectangle(Block[i].x*_CurrTileSet->GetTileWidth(), Block[i].y*_CurrTileSet->GetTileHeight(),
            Block[i].w*_CurrTileSet->GetTileWidth(), Block[i].h*_CurrTileSet->GetTileHeight());
        Engine::Instance().CurrentScene().AddGameObj(ColliderObj);
    }
    //TODO move this gambiarra to a more suitable place
    Camera::Boundaries = Rectangle(0,0, _MapWidth*_CurrTileSet->GetTileWidth(), _MapHeight * _CurrTileSet->GetTileHeight());
}

//__________________________________