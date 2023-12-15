#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
// #include "Legacy/TitleScene.hpp"
#include "TestScene.hpp"
#include "Scene/MainMenu.hpp"
#include "Scene/MainGame.hpp"
#include "Core/Engine.hpp"
#include "Tools/JsonParser.hpp"
#include "DTO/DialogueDTO.hpp"


int main (int argc, char** argv) 
{
    // TitleScene* Begin = new TitleScene(); //Penguin
    // Test01* Begin = new Test01();//Tests

    Engine::Instance("Give It Back!", 1280, 720, 1280, 720, false).Push(new MainMenu);
    // MainMap* Begin = new MainMap();
    // Engine::Instance("Give It Back!", 1280, 720, 1280, 720, false).Push(Begin);
    Engine::Instance().Run();

    return 0;    
}