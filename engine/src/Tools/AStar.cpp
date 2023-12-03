#include "Tools/AStar.hpp"

int AStar::_dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
int AStar::_dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

std::vector<Point> AStar::Search(const std::vector<std::vector<int>>& Grid, const Point& Start, const Point& Goal) 
{
    if(Grid[Start.y][Start.x] != -1 || Grid[Goal.y][Goal.x] != -1
        || Start.y >= Grid.size() || Start.x >= Grid[0].size()
        || Goal.y >= Grid.size() || Goal.x >= Grid[0].size())
    {
        return std::vector<Point>();
    }
    int Rows = Grid.size();
    int Columns = Grid[0].size();
    std::vector<Point> Path;
    auto Compare = [](const AStar::Node& A, const AStar::Node& B){return A.TotalCost > B.TotalCost;};
    std::priority_queue<AStar::Node, std::vector<AStar::Node>, decltype(Compare)> OpenNodes(Compare);
    std::vector<std::vector<bool>> ClosedList(Rows, std::vector<bool>(Columns, false));
    std::vector<std::vector<Point>> Parent(Rows, std::vector<Point>(Columns, {-1, -1}));

    AStar::Node StartNode = {Start, 0, _CalculateHeuristic(Start, Goal)};
    OpenNodes.push(StartNode);

    while (!OpenNodes.empty()) 
    {
        AStar::Node CurrentNode = OpenNodes.top();
        OpenNodes.pop();
        Point CurrentPoint = CurrentNode.Coordinates;
        if (CurrentPoint.x == Goal.x && CurrentPoint.y == Goal.y) 
        {
            while (CurrentPoint.x != -1 || CurrentPoint.y != -1) 
            {
                Path.push_back(CurrentPoint);
                CurrentPoint = Parent[CurrentPoint.y][CurrentPoint.x];
            }
            std::reverse(Path.begin(), Path.end());
            return Path;
        }

        ClosedList[CurrentPoint.y][CurrentPoint.x] = true;
        for (int i = 0; i < 8; ++i) 
        {
            int NextX = CurrentPoint.x + _dx[i];
            int NextY = CurrentPoint.y + _dy[i];

            if (_IsValid(NextX, NextY, Rows, Columns) && !ClosedList[NextY][NextX] && Grid[NextY][NextX] < 0 )
            {
                float NewCost = CurrentNode.Cost + 1;

                if (i >= 4 && _HasObstacle(Grid, CurrentPoint, {NextX, NextY})) 
                {
                    continue;//Diagonal move with obstacles not allowed
                }

                AStar::Node Neighbor = {{NextX, NextY}, NewCost, _CalculateHeuristic({NextX, NextY}, Goal)};
                Neighbor.TotalCost = Neighbor.Cost + Neighbor.Heuristic;
                OpenNodes.push(Neighbor);
                Parent[NextY][NextX] = CurrentPoint;
            }
        }
    }
    return std::vector<Point>();
}

float AStar::_CalculateHeuristic(const Point& Current, const Point& Goal)
{
    return std::abs(Current.x - Goal.x) + std::abs(Current.y - Goal.y);
}

bool AStar::_IsValid(int x, int y, int r, int c)
{
    return x >= 0 && x < c && y >= 0 && y < r;
}

bool AStar::_HasObstacle(const std::vector<std::vector<int>>& Grid, const Point& From, const Point& To)
{
    int x1 = To.x - From.x;
    int y1 = To.y - From.y;
    if((_IsValid(From.x + x1, From.y, Grid.size(), Grid[0].size()) && Grid[From.y][From.x + x1] != -1) 
        && (_IsValid(From.x, From.y + y1, Grid.size(), Grid[0].size()) && Grid[From.y + y1][From.x] != -1)
        && (_IsValid(From.x + x1, From.y + y1, Grid.size(), Grid[0].size()) && Grid[From.y + y1][From.x + x1] != -1))
    {
        return true;
    }
    return false;
}

std::vector<std::vector<int>> AStar::TrimSubgrid(const std::vector<std::vector<int>>& Grid, int StartRow, int StartCol, int NumRows, int NumCols)
{
    StartRow = (StartRow < 0 ? 0 : (StartRow >= Grid.size() ?  Grid.size()-1 : StartRow));
    StartCol = (StartCol < 0 ? 0 : (StartCol >= Grid[0].size() ?  Grid[0].size()-1 : StartCol));
    NumRows =  (NumRows <= 0 ? 1 : (StartRow+NumRows > Grid.size() ? Grid.size() - StartRow : NumRows));
    NumCols =  (NumCols <= 0 ? 1 : (StartCol+NumCols > Grid[0].size() ? Grid[0].size() - StartCol : NumCols));
    std::vector<std::vector<int>> Subgrid;
    Subgrid.reserve(NumRows);
    for (int i = StartRow; i < StartRow + NumRows; i++) 
    {
        std::vector<int> Row;
        Row.reserve(NumCols);
        for (int j = StartCol; j < StartCol + NumCols; j++) 
        {
            Row.push_back(Grid[i][j]);
        }
        Subgrid.push_back(Row);
    }
    return Subgrid;
}