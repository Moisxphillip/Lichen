#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
#include "../lib/TitleState.hpp"
#include "../../engine/lib/Engine.hpp"

int main (int argc, char** argv) 
{
    TitleState* Begin = new TitleState();
    Engine::Instance().Push(Begin);
    Engine::Instance().Run(); //Create a Engine instance by calling Get.. then run it

    return 0;
}