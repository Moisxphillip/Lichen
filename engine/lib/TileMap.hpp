#ifndef LICHEN_TILEMAP
#define LICHEN_TILEMAP

#include <vector>

#include "TileSet.hpp"

class TileMap: public Component
{
    private:
        std::vector<int> _TileMatrix;
        TileSet *_CurrTileSet;
        int _MapWidth;
        int _MapHeight;
        int _LayerArea;
        int _MapDepth;
        int _RefLayer;
        float _GetLayerMult(int);
        bool _RefLayerTurn;

    public:
        TileMap(GameObject&, std::string, TileSet*);
        ~TileMap();
        void Load(std::string);
        void SetTileSet(TileSet*);
        int& At(int, int, int);        
        void RenderLayer(int, int, int);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void SetRefLayer(int);

        //inheritance functions
        bool Is(std::string);
        void Render();
        void Start();
        void Update(float);
    
};



#endif//LICHEN_TILEMAP