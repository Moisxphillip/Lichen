#include "../lib/TitleState.hpp"
#include "../lib/StageState.hpp"
#include "../lib/Path.hpp"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Input.hpp"
#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Text.hpp"


TitleState::TitleState()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
	_Started = false;
}

TitleState::~TitleState()
{

}


void TitleState::LoadAssets()
{
    GameObject* Title = new GameObject(0);
    Sprite* TitleImage = new Sprite(*Title, FIMG_MAINSCR);
    Title->Box.Redimension(Vector2(TitleImage->GetWidth(),TitleImage->GetHeight()));
    Title->AddComponent(TitleImage);
    AddGameObj(Title);
    Cam.Follow(Title);

    GameObject* TitleDesc = new GameObject(1);
    Text* TitleText = new Text(*TitleDesc, FTTF_CALL, 30, Text::SOLID, "Press SPACE to start!", TextColor.ColorSDL());
    TitleDesc->Box.SetCenter(Title->Box.Center());
    TitleDesc->Box.y += 200;    
    TitleDesc->AddComponent(TitleText);
    AddGameObj(TitleDesc);
}

void TitleState::Update(float Dt)
{
    TextColorChange.Update(Dt);
    if(TextColorChange.Get() > 4)
    {
        TextColorChange.Restart();
    }

    //Rainbow effect
    float ColorMod = TextColorChange.Get()*90;
    TextColor.SetHSV(ColorMod, 100, 80);
    for(int i = 0; i< (int) (GameObjVec.size()); i++)
    {
        Text *ScrTxt = (Text*)GameObjVec[i]->GetComponent("Text");
        if(ScrTxt != nullptr)
        {
            ScrTxt->SetColor(TextColor.ColorSDL());
            break;
        }
    } 

    if(Input::Instance().KeyPress(K_SPACE))
    {
        StageState* Play = new StageState;
        Engine::Instance().Push(Play);
    }
    if((Input::Instance().IsKeyDown(K_ESC) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
    }
    // StateUpdate(Dt);
}

void TitleState::Render()
{
    // StateRender();
}


void TitleState::Start()
{
    LoadAssets();
    // StateStart();
}

void TitleState::Pause()
{

}

void TitleState::Resume()
{

}
