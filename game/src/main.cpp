#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
#include "../lib/TitleState.hpp"
#include "../../engine/lib/Game.hpp"

int main (int argc, char** argv) 
{
    TitleState* Begin = new TitleState();
    Game::Instance().Push(Begin);
    Game::Instance().Run(); //Create a game instance by calling Get.. then run it

    return 0;
}