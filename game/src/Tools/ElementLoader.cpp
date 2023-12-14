#include "Tools/ElementLoader.hpp"

#include <fstream>
#include <iomanip>

#include "Core/Engine.hpp"
#include "Components/Sprite.hpp"
#include "Components/Sound.hpp"
#include "Components/AACircle.hpp"
#include "Components/AARectangle.hpp"
#include "Tools/Emitter.hpp"
#include "Tools/Particles.hpp"
#include "Tools/DistanceTrigger.hpp"
#include "Tools/Tools.hpp"

#define TREE1 0
// #define TREE2 
#define TREE3 4

#define MUSH1 5
#define MUSH2 6

#define TOWER 13
#define SKY 14

#define HOUSE1 1
#define HOUSE2 2
#define HOUSE3 3

#define LEAFNOISE 9
#define SEANOISE 10

#define PARTGREENLEAF 11
#define PARTSPORE 12
#define PARTREDLEAF 15

#define SPAWNWORM 16
#define SPAWNBIRD 17
#define SPAWNMUSH 18

#define POS Vector2((Column)*64, (Row+1)*64)

void ElementLoader::LoadFromFile(std::string FilePath)
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
                case TREE1:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Tree1(POS));
                    break;

                case TREE3:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Tree3(POS));
                    break;

                case MUSH1:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Mush1(POS));
                    break;

                case MUSH2:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Mush2(POS));
                    break;

                case TOWER:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Tower(POS - Vector2(0,64)));
                    break;

                case SKY:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Sky(POS));
                    break;

                case HOUSE1:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::House1(POS));
                    break;

                case HOUSE2:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::House2(POS));
                    break;

                case HOUSE3:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::House3(POS));
                    break;

                case PARTGREENLEAF:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Leaves1(POS));
                    break;

                case PARTREDLEAF:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Leaves3(POS));
                    break;
                
                case PARTSPORE:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Spores(POS));
                    break;

                case SEANOISE:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::SeaNoise(POS));
                    break;

                case SPAWNBIRD:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Birds(POS));
                    break;

                case SPAWNWORM:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Worms(POS));
                    break;

                case SPAWNMUSH:
                    Engine::Instance().CurrentScene().AddGameObj(FastCreate::Smushs(POS));
                    break;

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

//##############################FASTCREATE##################################

GameObject* FastCreate::_DynamicObj()
{
    GameObject* Go = new GameObject();
    Go->Represents = CollisionMask::Terrain;
    Go->Depth = DepthMode::Dynamic;
    return Go;
}
void FastCreate::_LoadSprite(GameObject* Go, const std::string& File)
{
    Sprite* Spr = new Sprite(*Go, File);
    Go->AddComponent(Spr);
    Go->Box.Redimension(Vector2(Spr->GetWidth(), Spr->GetHeight()));
}

#include <iostream>
void FastCreate::_LoadPanSound(GameObject* Go, const std::string& File, int Volume)
{
    Sound* Snd = new Sound(*Go, File);
    Snd->Pan = true;
    Snd->Side = true;
    Snd->SetVolume(Volume);
    Go->AddComponent(Snd);
    Snd->Play(-1);
    // Snd->Stop();
    // DistanceTrigger* Dt = new DistanceTrigger(*Go, Snd, 1200, DistTriggerMode::Custom);
    // Dt->SetOnActivation(
    //     [Snd](){Snd->Play(20000);
    //     std::cout <<"Playing : " << Snd->Parent << '\n';
    //     }
    //     );
    // Dt->SetOnInactivation(
    //     [Snd](){Snd->Stop();
    //     std::cout <<"Stopping : " << Snd->Parent << '\n';
    //     ;}
    //     );
    // Go->AddComponent(Dt);
}

GameObject* FastCreate::Tree1(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/tree1.png");
    // _LoadPanSound(Go, "./res/audio/ambience/tree_leaves.ogg");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    AACircle* Col = new AACircle(*Go, ColliderKind::Stationary, Circle(0,0,29));
    Col->Offset = Vector2(0,115);
    Go->AddComponent(Col);
    return Go;
}

GameObject* FastCreate::Tree2(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/tree2.png");
    // _LoadPanSound(Go, "./res/audio/ambience/tree_leaves.ogg");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    AACircle* Col = new AACircle(*Go, ColliderKind::Stationary, Circle(0,0,22));
    Col->Offset = Vector2(0,140);
    Go->AddComponent(Col);
    return Go;
}

GameObject* FastCreate::Tree3(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/tree3.png");
    // _LoadPanSound(Go, "./res/audio/ambience/tree_leaves.ogg");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    AACircle* Col = new AACircle(*Go, ColliderKind::Stationary, Circle(0,0,22));
    Col->Offset = Vector2(0,140);
    Go->AddComponent(Col);
    return Go;
}

GameObject* FastCreate::Mush1(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/mush1.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    AACircle* Col = new AACircle(*Go, ColliderKind::Stationary, Circle(0,0,20));
    Col->Offset = Vector2(0,78);
    Go->AddComponent(Col);
    return Go;
}

GameObject* FastCreate::Mush2(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/mush2.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    AACircle* Col = new AACircle(*Go, ColliderKind::Stationary, Circle(0,0,20));
    Col->Offset = Vector2(0,86);
    Go->AddComponent(Col);
    return Go;
}

GameObject* FastCreate::Sky(Vector2 Position)
{
    GameObject* Go = new GameObject(-5);
    Go->Depth = DepthMode::Background;
    _LoadSprite(Go, "./res/img/prop/sky.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    return Go;
}

GameObject* FastCreate::Tower(Vector2 Position)
{
    GameObject* Go = new GameObject(-3);
    Go->Depth = DepthMode::Background;
    _LoadSprite(Go, "./res/img/prop/tower.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    return Go;
}

GameObject* FastCreate::House1(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/house1.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    return Go;
}

GameObject* FastCreate::House2(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/house2.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    return Go;
}

GameObject* FastCreate::House3(Vector2 Position)
{
    GameObject* Go = _DynamicObj();
    _LoadSprite(Go, "./res/img/prop/house3.png");
    Go->Box.SetPosition(Position - Vector2(0,Go->Box.h));
    Go->Box.h-=64;
    return Go;
}

GameObject* FastCreate::Leaves1(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 1.7f, Vector2(64*3, 64));//Adjust this later
    Go->Box.SetPosition(Position); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            Particle Z = PremadeParticles::Leaf1(Pos);
            ParticleManager::Instance().Emit(Z);
            return nullptr;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 1200));
    return Go;
}

GameObject* FastCreate::Leaves2(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 1.7f, Vector2(64*3, 64));//Adjust this later
    Go->Box.SetPosition(Position); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            Particle Z = PremadeParticles::Leaf2(Pos);
            ParticleManager::Instance().Emit(Z);
            return nullptr;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 1200));
    
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 900, DistTriggerMode::Disable));
    return Go;
}

GameObject* FastCreate::Leaves3(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 1.7f, Vector2(64*3, 64));//Adjust this later
    Go->Box.SetPosition(Position); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            Particle Z = PremadeParticles::Leaf3(Pos);
            ParticleManager::Instance().Emit(Z);
            return nullptr;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 1200));
    return Go;
}

GameObject* FastCreate::Spores(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 0.7f, Vector2(64.0f*9.0f,64.0f*9.0f));//Adjust this later
    Go->Box.SetPosition(Position - Vector2(64.0f * 4.5f, 64.0f * 4.5f)); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            Particle Z = PremadeParticles::Spore(Pos);
            ParticleManager::Instance().Emit(Z);
            return nullptr;
        });
    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 1200));
    return Go;
}

#include "Npc/Critter.hpp"
GameObject* FastCreate::Birds(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 10.0f, Vector2(64.0f*9.0f, 64.0f*9.0f));//Adjust this later
    Go->Box.SetPosition(Position - Vector2(64.0f * 4.5f, 64.0f * 4.5f)); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            if(Critter::CritterCount >= Critter::MaxCritterCount) 
            {
                return (GameObject*) nullptr;
            }
            GameObject* Obj = new GameObject();
            Obj->AddComponent(new Bird(*Obj));
            Obj->Box.SetPosition(Pos);
            return Obj;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 800, DistTriggerMode::Enable));
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 2500, DistTriggerMode::Disable));
    return Go;
}

GameObject* FastCreate::Worms(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 10.0f, Vector2(64.0f*5.0f, 64.0f*5.0f));//Adjust this later
    Go->Box.SetPosition(Position - Vector2(64.0f * 2.5f, 64.0f * 2.5f)); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            if(Critter::CritterCount >= Critter::MaxCritterCount) 
            {
                return (GameObject*) nullptr;
            }
            GameObject* Obj = new GameObject();
            Obj->AddComponent(new Worm(*Obj));
            Obj->Box.SetPosition(Pos);
            return Obj;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 800, DistTriggerMode::Enable));
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 2500, DistTriggerMode::Disable));
    return Go;
}

GameObject* FastCreate::Smushs(Vector2 Position)
{
    GameObject* Go = new GameObject();
    Emitter* Emt = new Emitter(*Go, 10.0f, Vector2(64.0f*4.0f, 64.0f*4.0f));//Adjust this later
    Go->Box.SetPosition(Position - Vector2(64.0f * 2.0f, 64.0f * 2.0f)); 
    Emt->SetEmitCall(
        [](Vector2 Pos)
        {
            if(Critter::CritterCount >= Critter::MaxCritterCount) 
            {
                return (GameObject*) nullptr;
            }
            GameObject* Obj = new GameObject();
            Obj->AddComponent(new SmallFungi(*Obj));
            Obj->Box.SetPosition(Pos);
            return Obj;
        });

    Go->AddComponent(Emt);
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 800, DistTriggerMode::Enable));
    Go->AddComponent(new DistanceTrigger(*Go, Emt, 2500, DistTriggerMode::Disable));
    return Go;
}

GameObject* FastCreate::SeaNoise(Vector2 Position)
{
    GameObject* Go = new GameObject();
    _LoadPanSound(Go, "./res/audio/ambience/sea.ogg", 70);
    Go->Box.SetPosition(Position);
    return Go;
}

GameObject* FastCreate::TreeNoise(Vector2 Position)
{
    GameObject* Go = new GameObject();
    _LoadPanSound(Go, "./res/audio/ambience/tree_leaves.ogg");
    Go->Box.SetPosition(Position);
    return Go;
}

void FastCreate::PlayOnce(const std::string& File, int Volume)
{
    GameObject* Go = new GameObject();
    Sound* Snd = new Sound(*Go, File);
    Snd->SelfDestruct = true;
    Snd->SetVolume(Volume);
    Snd->Play();
    Go->AddComponent(Snd);
    Engine::Instance().CurrentScene().AddGameObj(Go);
}

void FastCreate::PlayPanOnce(Vector2 Position, const std::string& File, int Volume)
{
    GameObject* Go = new GameObject();
    Go->Box.SetPosition(Position);
    Sound* Snd = new Sound(*Go, File);
    Snd->SelfDestruct = true;
    Snd->Pan = true;
    Snd->SetVolume(Volume);
    Go->AddComponent(Snd);
    Snd->Play();
    Engine::Instance().CurrentScene().AddGameObj(Go);
}