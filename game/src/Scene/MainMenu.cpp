#include "Scene/MainMenu.hpp"
#include "Scene/MainGame.hpp"
#include "Mechanics/Progress.hpp"
#include "Core/Input.hpp"
#include "Components/Sprite.hpp"
#include "Components/Fade.hpp"
#include "Components/CameraFollower.hpp"
#include "Core/Engine.hpp"

MainMenu::MainMenu()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
    Starting = false;
    ToPlay.SetLimit(2.0f);
}

MainMenu::~MainMenu()
{

}

void MainMenu::LoadAssets()
{
    Progress::ResetGame();

    GameObject* Go = new GameObject(52);
    Go->Depth = DepthMode::Foreground;
    Fade* Fd = new Fade(*Go, Color("#000000ff"), Color("#00000000"), 2.0f);
    Fd->Delete = true;
    Go->AddComponent(Fd);
    Go->AddComponent(new CameraFollower(*Go));
    AddGameObj(Go);

    Go = new GameObject();
    Go->AddComponent(new Sprite(*Go,"./res/img/title.png"));
    Go->Box.Redimension(Vector2(1280,720));
    Cam.Follow(Go);
    AddGameObj(Go);
}

void MainMenu::PhysicsUpdate(float Dt)
{    
}

void MainMenu::Update(float Dt)
{
    if(Input::Instance().KeyJustPressed(Key::Space) && !Starting)
    {
        GameObject* Go = new GameObject(52);
        Go->Depth = DepthMode::Foreground;
        Fade* Fd = new Fade(*Go, Color("#00000000"), Color("#000000ff"), 2.0f);
        Fd->Delete = true;
        Go->AddComponent(Fd);
        Go->AddComponent(new CameraFollower(*Go));
        AddGameObj(Go);
        Starting = true;
    }

    if(Starting)
    {
        ToPlay.Update(Dt);
        if(ToPlay.Finished())
        {
            Engine::Instance().Push(new MainMap);
        }
    }


    if(Input::Instance().QuitRequested())
	{
		_PopRequested = true;
		_QuitRequested = true;
    }
}

void MainMenu::Render()
{
}

void MainMenu::Start()
{
    LoadAssets();
}

void MainMenu::Pause()
{

}

void MainMenu::Resume()
{
    Starting = false;
    ToPlay.Restart();
    GameObject* Go = new GameObject(52);
    Go->Depth = DepthMode::Foreground;
    Fade* Fd = new Fade(*Go, Color("#000000ff"), Color("#00000000"), 2.0f);
    Fd->Delete = true;
    Go->AddComponent(Fd);
    Go->AddComponent(new CameraFollower(*Go));
    AddGameObj(Go);
}
