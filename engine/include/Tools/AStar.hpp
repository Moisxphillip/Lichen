#ifndef LICHEN_ASTARSEARCH
#define LICHEN_ASTARSEARCH

#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

struct Point 
{
    int x, y;
};


class AStar 
{
    public:
        //Returns a list of points from the Start to the Goal if a path is found, otherwise, returns an empty vector;
        static std::vector<Point> Search(const std::vector<std::vector<int>>& Grid, const Point& Start, const Point& Goal);
        
        //Makes a subgrid from the provided grid, having StartRow as y0, StartCol as x0 and following the specified width and height.
        //It also scales down the dimensions if somehow an invalid measurement is sent.
        static std::vector<std::vector<int>> TrimSubgrid(const std::vector<std::vector<int>>& Grid, int StartRow, int StartCol, int NumRows, int NumCols);
    private:
        struct Node
        {
            Point Coordinates;
            float Cost;
            float Heuristic;
            float TotalCost;
        };
        static int _dx[8];
        static int _dy[8];
        static float _CalculateHeuristic(const Point& Current, const Point& Goal);
        static bool _IsValid(int x, int y, int r, int c);
        static bool _HasObstacle(const std::vector<std::vector<int>>& Grid, const Point& From, const Point& To);
};

#endif//LICHEN_ASTARSEARCH