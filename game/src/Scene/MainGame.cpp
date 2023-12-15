#include "Scene/MainGame.hpp"

// #include "Dialogue.hpp"
#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Math/Physics.hpp"
#include "Components/AACircle.hpp"
#include "Components/AARectangle.hpp"
#include "Components/CameraFollower.hpp"
#include "Components/Fade.hpp"
#include "Components/Generic.hpp"
#include "Components/Sound.hpp"
#include "Components/Sprite.hpp"
#include "Components/Text.hpp"
#include "Components/TileMap.hpp"
#include "Tools/Xrand.hpp"
#include "Tools/Particles.hpp"

#include "Character/Player.hpp"

#include "Enemy/EnemyFactory.hpp"
#include "Enemy/Malachi.hpp"
#include "Enemy/FitzGerald.hpp"

#include "Mechanics/Inventory.hpp"
#include "Mechanics/Progress.hpp"

#include "Tools/ActiveArea.hpp"
#include "Tools/ElementLoader.hpp"
#include "Tools/DistanceTrigger.hpp"
#include "Tools/LoopSprite.hpp"
#include "Tools/MusicPlayer.hpp"
#include "Tools/TimedText.hpp"

#include "UserInterface/UIController.hpp"



std::vector<std::vector<int>>* MainMap::CollisionMap = nullptr;

MainMap::MainMap()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
    
}

MainMap::~MainMap()
{
}

Fade* AmbienceFader = nullptr;
Sound* AreaVillage = nullptr;
Sound* AreaForest = nullptr;
Sound* AreaMush = nullptr;

//Background disposition
#define WATER -6
#define GROUND -5
#define ABOVEGROUND -4
#define SHADOW -3

//Foreground Disposition
#define ABOVEPLAYER -4
#define ABOVEPLAYER2 -3
#define SCENARIOFADER -2
#define PARTICLES -1
#define UILAYER 50


void MainMap::LoadAssets()
{
    if(Progress::ShouldReset)
    {
        Progress::ResetGame();
    }
    else
    {
        Progress::PlayerStats.HP = 100;
        Progress::PlayerStats.Mana = 100;
        Progress::PlayerStats.Stamina = 3;
    }

    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->Box.SetCenter(Vector2(640, 750));
    playerObj->AddComponent(player);
    AddGameObj(playerObj);
    Cam.Follow(playerObj);
    
    //################################################ MAP
    //BACKGROUND
    GameObject* Tiles = new GameObject(GROUND);
    Tiles->Depth = DepthMode::Background;
    TileSet* Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    TileMap* Map = new TileMap(*Tiles, "./res/map/map_ground",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);
    Tiles = new GameObject(ABOVEGROUND);
    Tiles->Depth = DepthMode::Background;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveground",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);
    Tiles = new GameObject(SHADOW);
    Tiles->Depth = DepthMode::Background;
    Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    Map = new TileMap(*Tiles, "./res/map/map_shadow",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    //FOREGROUND
    Tiles = new GameObject(ABOVEPLAYER);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveplayer",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(ABOVEPLAYER2);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveplayer2",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(100);
    Tiles->Depth = DepthMode::Foreground;//TODO hide
    Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    Map = new TileMap(*Tiles, "./res/map/map_collision",Tset);
    Map->LoadCollision("./res/map/map_collision");
    Map->Enabled = false;
    CollisionMap = &(Map->_TileMatrix);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);
    //################################################
    
    GameObject* Fader = new GameObject(SCENARIOFADER);
    Fader->Depth = DepthMode::Foreground;
    AmbienceFader = new Fade(*Fader, Color("#00000000"), Color("#00000000"), 2);
    Fader->AddComponent(AmbienceFader);
    Fader->AddComponent(new CameraFollower(*Fader));
    AddGameObj(Fader);

    GameObject* Loops = new GameObject(WATER);
    LoopSprite* L = new LoopSprite(*Loops, "./res/img/tile/water.png");
    L->SetAnimationData(4, 1, 4, 0.25f);
    Loops->AddComponent(L);
    AddGameObj(Loops);
    
    ElementLoader::LoadFromFile("./res/map/map_props");
    
    GameObject* Inv = new GameObject();
    Inv->AddComponent(new Inventory(*Inv));
    AddGameObj(Inv);
    
    GameObject* UI = new GameObject();
    UI->Depth = DepthMode::Foreground;
    UI->SetLayer(UILAYER);
    UIController* Controller = new UIController(*UI);
    UI->AddComponent(new CameraFollower(*UI));
    UI->AddComponent(Controller);

    AddGameObj(UI);
    
    //####################################################### AMBIENT CONSTRUCTION
    GameObject* MPlayer = new GameObject();
    MPlayer->AddComponent(new MusicPlayer(*MPlayer));
    AddGameObj(MPlayer);

    GameObject* Go = new GameObject();
    ActiveArea* Aa = new ActiveArea(*Go, Rectangle(0,0,95*64,56*64));
    AreaVillage = new Sound(*Go, "./res/audio/ambience/prairie.ogg");
    // AreaVillage->SetVolume(127);
    Go->AddComponent(AreaVillage);
    Aa->SetOnActivation(
        []()
        {
            Color NumColor("#ffffff");
            std::string Prompt =  "Vila sem nome";
            GameObject* Place = new GameObject();
            Place->Depth = DepthMode::Foreground;
            Text* Txt = new Text(*Place,"./res/ttf/alagard.ttf", 50, TextStyle::BLENDED, Prompt, NumColor);
            Place->AddComponent(Txt);
            Place->AddComponent(new TimedText(*Place, Txt, NumColor, 0.5f, 2.5f, 0.5f));
            CameraFollower* Cf = new CameraFollower(*Place);
            Cf->Offset = Vector2(640 - Txt->GetDimensions().x*0.5f, 150);
            Place->AddComponent(Cf);
            Engine::Instance().CurrentScene().AddGameObj(Place);
            AmbienceFader->SetFinishColor(Color("#00000000"));
            if(AreaVillage)
            {
                AreaVillage->SetVolume(127);
                AreaVillage->Play(-1, 1000);
            }
            if(MusicPlayer::Self)
            {
                MusicPlayer::Self->PlaceSong("./res/audio/ost/village.ogg");
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AreaVillage)
            {
                AreaVillage->Stop(1000);
            }
        }
    );

    Go->AddComponent(Aa);
    AddGameObj(Go);
    Go = new GameObject();
    Aa = new ActiveArea(*Go, Rectangle(0, 56.1f*64, 95*64, 60*64));
    AreaForest = new Sound(*Go, "./res/audio/ambience/forest.ogg");
    AreaForest->SetVolume(127);
    Go->AddComponent(AreaForest);
    Aa->SetOnActivation(
        []()
        {
            Color NumColor("#ffffff");
            std::string Prompt =  "Floresta foda";
            GameObject* Place = new GameObject();
            Place->Depth = DepthMode::Foreground;
            Text* Txt = new Text(*Place,"./res/ttf/alagard.ttf", 50, TextStyle::BLENDED, Prompt, NumColor);
            Place->AddComponent(Txt);
            Place->AddComponent(new TimedText(*Place, Txt, NumColor, 0.5f, 2.5f, 0.5f));
            CameraFollower* Cf = new CameraFollower(*Place);
            Cf->Offset = Vector2(640 - Txt->GetDimensions().x*0.5f, 150);
            Place->AddComponent(Cf);
            Engine::Instance().CurrentScene().AddGameObj(Place);
            AmbienceFader->SetFinishColor(Color("#12280940"));
            if(AreaForest)
            {
                AreaForest->SetVolume(127);
                AreaForest->Play(-1, 1000);
            }
            if(MusicPlayer::Self)
            {
                MusicPlayer::Self->PlaceSong("./res/audio/ost/forest.ogg");
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AreaForest)
            {
                AreaForest->Stop(1000);
            }
        }
    );

    Go->AddComponent(Aa);
    AddGameObj(Go);
    Go = new GameObject();
    Aa = new ActiveArea(*Go, Rectangle(95.1f*64,0, 54*64, 103*64));
    AreaMush = new Sound(*Go, "./res/audio/ambience/mushroom_forest.ogg");
    Go->AddComponent(AreaMush);
    AreaMush->SetVolume(127);
    Aa->SetOnActivation(
        []()
        {
            Color NumColor("#ffffff");
            std::string Prompt =  "Fungo no meu cerebro";
            GameObject* Place = new GameObject();
            Place->Depth = DepthMode::Foreground;
            Text* Txt = new Text(*Place,"./res/ttf/alagard.ttf", 50, TextStyle::BLENDED, Prompt, NumColor);
            Place->AddComponent(Txt);
            Place->AddComponent(new TimedText(*Place, Txt, NumColor, 0.5f, 2.5f, 0.5f));
            CameraFollower* Cf = new CameraFollower(*Place);
            Cf->Offset = Vector2(640 - Txt->GetDimensions().x*0.5f, 150);
            Place->AddComponent(Cf);
            Engine::Instance().CurrentScene().AddGameObj(Place);
            AmbienceFader->SetFinishColor(Color("#50148a33"));
            if(AreaMush)
            {
                AreaMush->SetVolume(127);
                AreaMush->Play(-1, 1000);
            }
            if(MusicPlayer::Self)
            {
                MusicPlayer::Self->PlaceSong("./res/audio/ost/fungi.ogg");
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AreaMush)
            {
                AreaMush->Stop(1000);
            }
        }
    );
    Go->AddComponent(Aa);
    AddGameObj(Go);

    //Particle system
    Go = new GameObject(PARTICLES);
    Generic* PartSys = new Generic(*Go, "Particle");
    PartSys->SetUpdate([]
        (float Dt, Generic* PartSys)
        {
            ParticleManager::Instance().Update(Dt);
        });
    PartSys->SetRender([]
        (Generic* PartSys)
        {
            ParticleManager::Instance().Render();
        });
    Go->AddComponent(PartSys);
    AddGameObj(Go);
    

    
    // GameObject* dialeobj = new GameObject(3);
    // slimeObj->AddComponent(new DialogueManager(*dialeobj, "ala.json"));
    // AddGameObj(dialeobj);
    // Dialogueobj->Box.SetCenter(Vector2(640, 150));

}

void MainMap::PhysicsUpdate(float Dt)
{    
}

#include "Enemy/Biagia.hpp"

void MainMap::Update(float Dt)
{
    Input& input = Input::Instance();

    //TODO remove all this and add cheats
    if(Player::Self == nullptr)
    {
            GameObject* playerObj = new GameObject();
            Player* player = new Player(*playerObj);
            playerObj->Box.SetCenter(Vector2(640, 750));
            playerObj->AddComponent(player);
            AddGameObj(playerObj);
    }

    if(Input::Instance().KeyJustPressed(Key::Number1)&& Player::Self != nullptr)
    {
        Player::Self->AddExperience(100);
    }
    if(Input::Instance().KeyJustPressed(Key::Number2) && Malachi::Self == nullptr)
    {
            GameObject* Obj = new GameObject();
            FitzGerald* Fz= new FitzGerald(*Obj);
            Obj->Box.SetCenter(Input::Instance().MousePosition());
            Obj->AddComponent(Fz);
            AddGameObj(Obj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number4) && Malachi::Self == nullptr)
    {
        GameObject* Obj = new GameObject();
        FitzGerald* Mala = new FitzGerald(*Obj);
        Obj->Box.SetCenter(Input::Instance().MousePosition());
        Obj->AddComponent(Mala);
        AddGameObj(Obj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number3) && Biagia::Self == nullptr)
    {
        GameObject* Obj = new GameObject();
        Biagia* Mala = new Biagia(*Obj);
        Obj->Box.SetCenter(Input::Instance().MousePosition());
        Obj->AddComponent(Mala);
        AddGameObj(Obj);
    }

    if(Input::Instance().KeyJustPressed(Key::F1))//TODO change to scene change trigger
    {
        _PopRequested = true;
        if(Player::Self && Player::Self->GetStats().HP > 0)
        {
            Progress::PlayerStats = Player::Self->GetStats();
        }
        Engine::Instance().Push(new FitzMap);
    }

    if(Input::Instance().QuitRequested())
	{
		_PopRequested = true;
		_QuitRequested = true;
    }
}

void MainMap::Render()
{
}

void MainMap::Start()
{
    LoadAssets();
}

void MainMap::Pause()
{

}

void MainMap::Resume()
{

}

// #include "Scene/FitzMap.hpp"
// #include "Scene/MainGame.hpp"
// #include "Mechanics/Progress.hpp"
// #include "Core/Input.hpp"
// #include "Components/Sprite.hpp"
// #include "Components/Fade.hpp"
// #include "Components/CameraFollower.hpp"
// #include "Core/Engine.hpp"

FitzMap::FitzMap()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
}

FitzMap::~FitzMap()
{
}

void FitzMap::LoadAssets()
{
    // Progress::ResetGame();
    GameObject* MPlayer = new GameObject();
    MPlayer->AddComponent(new MusicPlayer(*MPlayer));
    AddGameObj(MPlayer);

    GameObject* Go = new GameObject(52);
    Go->Depth = DepthMode::Foreground;
    Fade* Fd = new Fade(*Go, Color("#000000ff"), Color("#00000000"), 2.0f);
    Fd->Delete = true;
    Go->AddComponent(Fd);
    Go->AddComponent(new CameraFollower(*Go));
    AddGameObj(Go);

    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->Box.SetCenter(Vector2(640, 400));
    playerObj->AddComponent(player);
    AddGameObj(playerObj);
    Cam.Follow(playerObj);

    GameObject* Obj = new GameObject();
    FitzGerald* Mala = new FitzGerald(*Obj);
    Obj->Box.SetCenter(Vector2(640, 200));
    Obj->AddComponent(Mala);
    AddGameObj(Obj);
    
    // Go = new GameObject();
    // Go->AddComponent(new Sprite(*Go,"./res/img/title.png"));
    // Go->Box.Redimension(Vector2(1280,720));
    // Cam.Follow(Go);
    // AddGameObj(Go);
}

void FitzMap::PhysicsUpdate(float Dt)
{    
}

void FitzMap::Update(float Dt)
{
    // if(Input::Instance().KeyJustPressed(Key::Space) && !Starting)
    // {
    //     GameObject* Go = new GameObject(52);
    //     Go->Depth = DepthMode::Foreground;
    //     Fade* Fd = new Fade(*Go, Color("#00000000"), Color("#000000ff"), 2.0f);
    //     Fd->Delete = true;
    //     Go->AddComponent(Fd);
    //     Go->AddComponent(new CameraFollower(*Go));
    //     AddGameObj(Go);
    //     Starting = true;
    // }

    if(Input::Instance().KeyJustPressed(Key::Escape) || Player::Self == nullptr)
    // if(Player::Self == nullptr)//Use this later
    {      
		_PopRequested = true;
        Progress::ShouldReset = false;
        Engine::Instance().Push(new MainMap);
    }


    if(Input::Instance().QuitRequested())
	{
		_PopRequested = true;
		_QuitRequested = true;
    }
}

void FitzMap::Render()
{
}

void FitzMap::Start()
{
    LoadAssets();
}

void FitzMap::Pause()
{

}

void FitzMap::Resume()
{
    // Starting = false;
    // ToPlay.Restart();
}
























    // ______________________________________________________ Added logic___________________

//     if(text && Engine::Instance().GetPing())
//     {
//         text->SetText(std::to_string(1.0f/Dt) + " Fps");
//     }

   
//     if(Input::Instance().KeyJustPressed(Key::Number1))
//     {
//         // GameObject* slimeObj = new GameObject();
//         // Slime* slime = new Slime(*slimeObj);
//         // slimeObj->Box.SetCenter(Input::Instance().MousePosition());
//         // slimeObj->AddComponent(slime);
//         // AddGameObj(slimeObj);


//         GameObject* slimeObj = new GameObject();
//         EnemyType enmy = static_cast<EnemyType> (Engine::RandomUint() % (int)EnemyType::TOTAL);
//         std::cout<<enmy<<std::endl;

//         slimeObj->AddComponent(EnemyFactory::CreateEnemy(*slimeObj, EnemyType::SLIME, Input::Instance().MousePosition()));
//         AddGameObj(slimeObj);
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number2) && Player::Self == nullptr)
//     {
//             GameObject* playerObj = new GameObject();
//             Player* player = new Player(*playerObj);
//             playerObj->Box.SetCenter(Vector2(640, 750));
//             playerObj->AddComponent(player);
//             AddGameObj(playerObj);
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number3) && Malachi::Self == nullptr)
//     {
//             GameObject* Obj = new GameObject();
//             Malachi* Mala = new Malachi(*Obj);
//             Obj->Box.SetCenter(Input::Instance().MousePosition());
//             Obj->AddComponent(Mala);
//             AddGameObj(Obj);
//     }

//     if(Input::Instance().KeyJustPressed(Key::Number8))
//     {
//         AmbienceFader->SetFinishColor(Color("#1228093a"));
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number9))
//     {
//         AmbienceFader->SetFinishColor(Color("#50148a33"));
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number0))
//     {
//         AmbienceFader->SetFinishColor(Color("#00000000"));
//     }

//     ParticleManager::Instance().Update(Dt);
//     if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
// 	{
// 		_PopRequested = true;
// 		_QuitRequested = true;
//         text = nullptr;
//     }
// }

// void MainMap::Render()
// {
//     ParticleManager::Instance().Render();
// }


// void MainMap::Start()
// {
//     LoadAssets();
// }

// void MainMap::Pause()
// {

// }

// void MainMap::Resume()
// {

// }
