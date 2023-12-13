#ifndef GAME_LOADER
#define GAME_LOADER

#include <string>
#include "Core/GameObject.hpp"

class ElementLoader
{
    public:
        static void LoadFromFile(std::string FilePath);
};

class FastCreate
{
        static GameObject* _DynamicObj();
        static void _LoadSprite(GameObject* Go, const std::string& File);
        static void _LoadPanSound(GameObject* Go, const std::string& File, int Volume=255);
        
    public:
        static GameObject* Tree1(Vector2 Position);
        static GameObject* Tree2(Vector2 Position);
        static GameObject* Tree3(Vector2 Position);

        static GameObject* Mush1(Vector2 Position);
        static GameObject* Mush2(Vector2 Position);
        
        static GameObject* Sky(Vector2 Position);
        static GameObject* Tower(Vector2 Position);
        
        static GameObject* House1(Vector2 Position);
        static GameObject* House2(Vector2 Position);
        static GameObject* House3(Vector2 Position);
        
        static GameObject* Leaves1(Vector2 Position);
        static GameObject* Leaves2(Vector2 Position);
        static GameObject* Leaves3(Vector2 Position);
        static GameObject* Spores(Vector2 Position);

        static GameObject* SeaNoise(Vector2 Position);
        static GameObject* TreeNoise(Vector2 Position);
        //general helpers

        static void PlayOnce(const std::string& File, int Volume=255);
        static void PlayPanOnce(Vector2 Position, const std::string& File, int Volume=255);

};

#endif//GAME_LOADER