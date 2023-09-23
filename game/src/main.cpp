#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
#include "../lib/TitleScene.hpp"
#include "../lib/TestScene.hpp"
#include "../../engine/lib/Engine.hpp"

int main (int argc, char** argv) 
{
    TitleScene* Begin = new TitleScene(); //Penguin
    // Test01* Begin = new Test01();//Tests
    Engine::Instance().Push(Begin);
    Engine::Instance().Run();
    return 0;    
}