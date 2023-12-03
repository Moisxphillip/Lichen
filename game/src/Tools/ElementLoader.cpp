#include "Tools/ElementLoader.hpp"

#include <fstream>
#include <iomanip>

#include "Tools/Tools.hpp"

void ElementLoader::Load(std::string FilePath)
{
    std::ifstream TextMap(FilePath+".csv");
    if(!TextMap.is_open())
    {
        Error("ElementLoader::Load: File could not be opened");
        return;
    }

    std::string Entry;//Will collect each input for interpretation and storage
    int Column = 0, Row = 0;

    while(!TextMap.eof()) 
    {
        std::getline(TextMap, Entry, '\n');
        std::stringstream Line(Entry);

        for (int i; Line >> i;) 
        {
            switch(i) //Here we specify what each instruction should place on the map
            {
                
                default:
                    break;
            }


            if (Line.peek() == ',' or Line.peek() == '\n') 
            {
                Line.ignore();
            }
            Column++;
        }
        if (TextMap.eof()) 
        {
            break;
        }
        Column = 0; //Resets the column count
        Row++;
    }
    TextMap.close();
}