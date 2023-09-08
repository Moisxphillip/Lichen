#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
#include "../lib/TitleState.hpp"
#include "../lib/TestState.hpp"
#include "../../engine/lib/Engine.hpp"

int main (int argc, char** argv) 
{
    // TitleState* Begin = new TitleState(); //Penguin
    Test01* Begin = new Test01();//Tests
    Engine::Instance().Push(Begin);
    Engine::Instance().Run();
    return 0;    
}