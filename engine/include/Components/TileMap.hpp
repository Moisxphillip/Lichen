#ifndef LICHEN_TILEMAP
#define LICHEN_TILEMAP

#include <vector>

#include "Components/TileSet.hpp"

struct RectInt
{
    int x, y, w, h;
};

class TileMap: public Component
{
    private:
        TileSet *_CurrTileSet;
        int _MapWidth;
        int _MapHeight;
        float _Parallax;
        int _LowerMarker;

        //Collision automation functions
        int _Hash(std::vector<std::vector<int>>& Matrix);
        bool _HasMapChanged(int HashResult, std::string HashPath);
        std::vector<RectInt> _LoadCoord(std::string Path);
        void _DumpCoord(const std::vector<RectInt>& Data, std::string Path);
        void _BorderMarking(std::vector<std::vector<int>>& Map);
        void _FindX(std::vector<std::vector<int>>& Map);
        std::vector<RectInt> _MapToCoord(std::vector<std::vector<int>>& Map);
        void _CoordOptimizer(std::vector<RectInt>& Coords);

    public:
        bool Enabled;
        std::vector<std::vector<int>> _TileMatrix;
        TileMap(GameObject& Parent, std::string Path, TileSet* Tiles, bool LoadAsLegacy=false, bool IsZeroEmpty=true);
        ~TileMap();
        void Load(std::string Path);
        void LoadCSV(std::string Path);
        void SetTileSet(TileSet* Tiles);
        int GetWidth();
        int GetHeight();
        void SetParallax(float);
        float GetParallax();
        void LoadCollision(std::string FileName);

        //inheritance functions
        void Render();
};



#endif//LICHEN_TILEMAP