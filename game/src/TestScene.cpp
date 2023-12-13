#include "TestScene.hpp"
#include "Dummy.hpp"
#include "Enemy/Slime.hpp"
// #include "Dialogue.hpp"
#include "Enemy/EnemyFactory.hpp"
#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Graphics/Draw.hpp"
#include "Math/Physics.hpp"
#include "Tools/Particles.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include "Components/AACircle.hpp"
#include "Components/AARectangle.hpp"
#include "Components/TileMap.hpp"
#include "Components/CameraFollower.hpp"
#include "Components/CameraFollower.hpp"
#include "Components/Fade.hpp"
#include "UserInterface/UIController.hpp"
#include "Mechanics/Inventory.hpp"
#include "Enemy/Slime.hpp"
#include "Character/Player.hpp"
#include "Tools/LoopSprite.hpp"
#include "Tools/ActiveArea.hpp"
#include "Tools/DistanceTrigger.hpp"
#include "Tools/ElementLoader.hpp"
#include "Components/Sound.hpp"
#include "Enemy/Malachi.hpp"


#include "Tools/Xrand.hpp"

std::vector<std::vector<int>>* Test01::CollisionMap = nullptr;

Test01::Test01()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
    
}

Test01::~Test01()
{
}

Text* text = nullptr;
Fade* _Fader = nullptr;
Sound* AmbVilla = nullptr;
Sound* AmbForest = nullptr;
Sound* AmbMush = nullptr;


#include "Components/CameraFollower.hpp"
#include "Tools/TimedText.hpp"

void Test01::LoadAssets()
{
 
    Engine::Instance().GetRenderer().SetClearColor((std::string)"#4c0317");

    GameObject* imgo = new GameObject();
    imgo->Depth = DepthMode::Foreground;
    text = new Text(*imgo, "./res/ttf/Caviar.ttf", 20, TextStyle::BLENDED, ".", Color("#ffffff"));
    imgo->Box.x = 0;
    imgo->Box.y = 0;
    imgo->AddComponent(text);
    imgo->AddComponent(new CameraFollower(*imgo));
    AddGameObj(imgo);

    GameObject* playerObj = new GameObject();
    Player* player = new Player(*playerObj);
    playerObj->Box.SetCenter(Vector2(640, 750));
    playerObj->AddComponent(player);
    AddGameObj(playerObj);
    Cam.Follow(playerObj);

    
    //################################################
    //TODO Set numbers correctly after defining layer distribution
    GameObject* Tiles = new GameObject(-5);
    Tiles->Depth = DepthMode::Background;
    TileSet* Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    TileMap* Map = new TileMap(*Tiles, "./res/map/map_ground",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-4);
    Tiles->Depth = DepthMode::Background;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveground",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);
    
    Tiles = new GameObject(-3);
    Tiles->Depth = DepthMode::Background;
    Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    Map = new TileMap(*Tiles, "./res/map/map_shadow",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-4);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveplayer",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(-3);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/tile/aboveground.png");
    Map = new TileMap(*Tiles, "./res/map/map_aboveplayer2",Tset);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);

    Tiles = new GameObject(100);
    Tiles->Depth = DepthMode::Foreground;
    Tset = new TileSet(64,64, "./res/img/tile/ground.png");
    Map = new TileMap(*Tiles, "./res/map/map_collision",Tset);
    Map->LoadCollision("./res/map/v2/mapa_v2");
    Map->Enabled = false;
    CollisionMap = &(Map->_TileMatrix);
    Tiles->AddComponent(Map);
    AddGameObj(Tiles);
    //################################################
    
    GameObject* Fader = new GameObject(200);
    Fader->Depth = DepthMode::Foreground;
    _Fader = new Fade(*Fader, Color("#00000000"), Color("#00000000"), 2);
    Fader->AddComponent(_Fader);
    Fader->AddComponent(new CameraFollower(*Fader));
    AddGameObj(Fader);


    GameObject* Loops = new GameObject(-10);
    LoopSprite* L = new LoopSprite(*Loops, "./res/img/tile/water.png");
    L->SetAnimationData(4, 1, 4, 0.25f);
    Loops->AddComponent(L);
    AddGameObj(Loops);

    GameObject* Inv = new GameObject();
    Inv->AddComponent(new Inventory(*Inv));
    AddGameObj(Inv);
    
    
    GameObject* UI = new GameObject();
    UI->Depth = DepthMode::Foreground;
    UI->SetLayer(50);
    UIController* Controller = new UIController(*UI);
    UI->AddComponent(new CameraFollower(*UI));
    UI->AddComponent(Controller);

    AddGameObj(UI);
    
    //#######################################################
    GameObject* Go = new GameObject();
    ActiveArea* Aa = new ActiveArea(*Go, Rectangle(0,0,95*64,56*64));
    AmbVilla = new Sound(*Go, "./res/audio/ambience/prairie.ogg");
    Go->AddComponent(AmbVilla);
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
            _Fader->SetFinishColor(Color("#00000000"));
            if(AmbVilla)
            {
                AmbVilla->SetVolume(127);
                AmbVilla->Play(-1, 1000);
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AmbVilla)
            {
                AmbVilla->Stop(1000);
            }
        }
    );


    Go->AddComponent(Aa);
    AddGameObj(Go);
    Go = new GameObject();
    Aa = new ActiveArea(*Go, Rectangle(0, 56.1f*64, 95*64, 60*64));
    AmbForest = new Sound(*Go, "./res/audio/ambience/forest.ogg");
    Go->AddComponent(AmbForest);
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
            _Fader->SetFinishColor(Color("#12280940"));
            if(AmbForest)
            {
                AmbForest->SetVolume(127);
                AmbForest->Play(-1, 1000);
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AmbForest)
            {
                AmbForest->Stop(1000);
            }
        }
    );

    Go->AddComponent(Aa);
    AddGameObj(Go);
    Go = new GameObject();
    Aa = new ActiveArea(*Go, Rectangle(95.1f*64,0, 54*64, 103*64));
    AmbMush = new Sound(*Go, "./res/audio/ambience/mushroom_forest.ogg");
    Go->AddComponent(AmbMush);
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
            _Fader->SetFinishColor(Color("#50148a33"));
            if(AmbMush)
            {
                AmbMush->SetVolume(127);
                AmbMush->Play(-1, 1000);
            }
        }
    );
    Aa->SetOnInactivation(
        []()
        {
            if(AmbMush)
            {
                AmbMush->Stop(1000);
            }
        }
    );
    Go->AddComponent(Aa);
    AddGameObj(Go);

    
    // GameObject* dialeobj = new GameObject(3);
    // slimeObj->AddComponent(new DialogueManager(*dialeobj, "ala.json"));
    // AddGameObj(dialeobj);
    // Dialogueobj->Box.SetCenter(Vector2(640, 150));

    ElementLoader::LoadFromFile("./res/map/map_props");
}

void Test01::PhysicsUpdate(float Dt)
{    
    //TODO transfer to appropriate place, add the masks to it

}

#include "Tools/Emitter.hpp"
void Test01::Update(float Dt)
{
    Input& input = Input::Instance();

    //Creating emitters


    if(text && Engine::Instance().GetPing())
    {
        text->SetText(std::to_string(1.0f/Dt) + " Fps");
    }

   
    if(Input::Instance().KeyJustPressed(Key::Number1))
    {
        GameObject* slimeObj = new GameObject();
        slimeObj->AddComponent(EnemyFactory::CreateEnemy(*slimeObj, EnemyType::SLIME, Input::Instance().MousePosition()));
        AddGameObj(slimeObj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number2) && Player::Self == nullptr)
    {
            GameObject* playerObj = new GameObject();
            Player* player = new Player(*playerObj);
            playerObj->Box.SetCenter(Vector2(640, 750));
            playerObj->AddComponent(player);
            AddGameObj(playerObj);
    }
    if(Input::Instance().KeyJustPressed(Key::Number3) && Malachi::Self == nullptr)
    {
            GameObject* Obj = new GameObject();
            Malachi* Mala = new Malachi(*Obj);
            Obj->Box.SetCenter(Input::Instance().MousePosition());
            Obj->AddComponent(Mala);
            AddGameObj(Obj);
    }

    if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        text = nullptr;
    }

    ParticleManager::Instance().Update(Dt);//TODO give this to a generic object in the correct layer
}

void Test01::Render()
{
    ParticleManager::Instance().Render();//TODO give this to a generic object in the correct layer
}

void Test01::Start()
{
    LoadAssets();
}

void Test01::Pause()
{

}

void Test01::Resume()
{

}


// //Testing map V1
    // GameObject* Tiles = new GameObject(-5);
    // Tiles->Depth = DepthMode::Background;
    // TileSet* Tset = new TileSet(64,64, "./res/img/Tiles/Ground.png");
    // TileMap* Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_ground",Tset);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    // Tiles = new GameObject(-4);
    // Tiles->Depth = DepthMode::Background;
    // Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    // Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AboveGround",Tset);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    // Tiles = new GameObject(-4);
    // Tiles->Depth = DepthMode::Foreground;
    // Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    // Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AbovePlayer",Tset);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    // Tiles = new GameObject(-3);
    // Tiles->Depth = DepthMode::Foreground;
    // Tset = new TileSet(64,64, "./res/img/Tiles/AboveGround.png");
    // Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_AbovePlayer2",Tset);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);

    // Tiles = new GameObject(100);
    // Tiles->Depth = DepthMode::Foreground;
    // Tset = new TileSet(64,64, "./res/img/Tiles/Ground.png");
    // Map = new TileMap(*Tiles, "./res/map/v1/mapa_v1_collision",Tset);
    // Map->LoadCollision("./res/map/v1/mapa_v1");
    // Map->Enabled = false;
    // CollisionMap = &(Map->_TileMatrix);
    // Tiles->AddComponent(Map);
    // AddGameObj(Tiles);


        // GameObject* slimeObj = new GameObject();
        // Slime* slime = new Slime(*slimeObj);
        // slimeObj->Box.SetCenter(Input::Instance().MousePosition());
        // slimeObj->AddComponent(slime);
        // AddGameObj(slimeObj);

// int _Type = 0;
    
    // if(input.KeyJustPressed(Key::Equal))
    // {
    //     _Type++;
    //     _Type = _Type > 15 ? 0 : _Type;
    //     std::cout <<_Type << '\n';
    // }
    // else if(input.KeyJustPressed(Key::Minus))
    // {
    //     _Type--;
    //     _Type = _Type < 0 ? 15 : _Type;
    //     std::cout <<_Type << '\n';
    // }


    // GameObject* Snd = new GameObject();
    // Snd->Box.SetPosition(Vector2(1200,1200));
    // Sound* Sd = new Sound(*Snd, "./res/audio/dirt.ogg");
    // Sd->Pan = true;
    // Sd->Play(100);
    // Snd->AddComponent(Sd);
    // Sprite* Sprt = new Sprite(*Snd, "./res/galor.png");
    // Snd->AddComponent(Sprt);
    // DistanceTrigger* Dt = new DistanceTrigger(*Snd, Sprt, 400);
    // // DistanceTrigger* Dt = new DistanceTrigger(*Snd, Sd, 400, DistTriggerMode::Custom);
    // // Dt->SetOnActivation(
    // //     [Sd](){Sd->Play();}
    // // );
    // // Dt->SetOnInactivation(
    // //     [Sd](){Sd->Stop();}
    // // );
    // Snd->AddComponent(Dt);
    // AddGameObj(Snd);


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
//         _Fader->SetFinishColor(Color("#1228093a"));
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number9))
//     {
//         _Fader->SetFinishColor(Color("#50148a33"));
//     }
//     if(Input::Instance().KeyJustPressed(Key::Number0))
//     {
//         _Fader->SetFinishColor(Color("#00000000"));
//     }

//     ParticleManager::Instance().Update(Dt);
//     if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
// 	{
// 		_PopRequested = true;
// 		_QuitRequested = true;
//         text = nullptr;
//     }
// }

// void Test01::Render()
// {
//     ParticleManager::Instance().Render();
// }


// void Test01::Start()
// {
//     LoadAssets();
// }

// void Test01::Pause()
// {

// }

// void Test01::Resume()
// {

// }
