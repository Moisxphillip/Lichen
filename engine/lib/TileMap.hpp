#ifndef LICHEN_TILEMAP
#define LICHEN_TILEMAP

#include <vector>

#include "TileSet.hpp"

struct RectInt
{
    int x, y, w, h;
};

class TileMap: public Component
{
    private:
        std::vector<std::vector<int>> _TileMatrix;
        TileSet *_CurrTileSet;
        int _MapWidth;
        int _MapHeight;
        float _Parallax;
        int _LowerMarker;

        //Collision automation functions
        int _Hash(std::vector<std::vector<int>>&);
        bool _HasMapChanged(int, std::string);
        std::vector<RectInt> _LoadCoord(std::string);
        void _DumpCoord(const std::vector<RectInt>&, std::string);
        void _BorderMarking(std::vector<std::vector<int>>&);
        void _FindX(std::vector<std::vector<int>>&);
        std::vector<RectInt> _MapToCoord(std::vector<std::vector<int>>&);
        void _CoordOptimizer(std::vector<RectInt>&);

    public:
        TileMap(GameObject&, std::string, TileSet*, bool, bool);
        ~TileMap();
        void Load(std::string);
        void LoadCSV(std::string);
        void SetTileSet(TileSet*);
        int GetWidth();
        int GetHeight();
        void SetParallax(float);
        float GetParallax();

        void LoadCollision(std::string fileName);

        void SetRefLayer(int);

        //inheritance functions
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);
    
};



#endif//LICHEN_TILEMAP