#include "../lib/EndState.hpp"
#include "../lib/Path.hpp"
#include "../lib/GameStats.hpp"

#include "../../engine/lib/Sprite.hpp"
#include "../../engine/lib/Text.hpp"
#include "../../engine/lib/Input.hpp"

EndState::EndState()
{
    _QuitRequested = false; //Allows loop until quit is requested
	_PopRequested = false;
    _EndMusic = nullptr;
	_Started = false;
}

EndState::~EndState()
{
    delete _EndMusic;
    _EndMusic = nullptr;
}


void EndState::LoadAssets()
{
    //Main Image
    GameObject* Title = new GameObject(1);
    Sprite* TitleImage;
    if(GameStats::PlayerVictory)
    {
        TitleImage = new Sprite(*Title, FIMG_WINSCR);
        _EndMusic = new Music(FMUS_STAGEWIN);
    }
    else
    {
        TitleImage = new Sprite(*Title, FIMG_LOSESCR);
        _EndMusic = new Music(FMUS_STAGELOSE);
    }
    Title->Box.Redimension(Vector2(TitleImage->GetWidth(),TitleImage->GetHeight()));
    Title->AddComponent(TitleImage);
    AddGameObj(Title);

    Cam.Follow(Title);

    //Victory status
    GameObject* TitleDesc = new GameObject(5);
    Text* TitleText;
    
    // TitleDesc->Box.y += 200; 
    if(GameStats::PlayerVictory)
    {
        TitleText = new Text(*TitleDesc, FTTF_CALL, 40, TextStyle::SOLID, "VICTORY!!!", TextColor);

    }
    else
    {
        TitleText = new Text(*TitleDesc, FTTF_CALL, 40, TextStyle::SOLID, "DEFEAT...", TextColor);
    }

    TitleDesc->Box.SetCenter(Title->Box.Center());
    if(GameStats::PlayerVictory)
    {
        TitleDesc->Box.y += 220;
    }
    else
    {
        TitleDesc->Box.y -= 250;
    }
   
    TitleDesc->AddComponent(TitleText);
    AddGameObj(TitleDesc);

    //Return Text
    GameObject* ReturnObj = new GameObject(5);
    Text* ReturnText = TitleText = new Text(*ReturnObj, FTTF_CALL, 20, TextStyle::SOLID, "Press SPACE to return to main screen.", TextColor);
    ReturnObj->Box.SetCenter(Title->Box.Center());
    ReturnObj->Box.y += 270;    
    ReturnObj->AddComponent(ReturnText);
    AddGameObj(ReturnObj);
    
    //Play song
	_EndMusic->Play(-1, 1000);
}

void EndState::Update(float Dt)
{
    TextColorChange.Update(Dt);
    if(TextColorChange.Get() > 4)
    {
        TextColorChange.Restart();
    }

    //Rainbow effect
    float ColorMod = TextColorChange.Get()*90;
    TextColor.SetHSV(ColorMod, 100, 80);
    for(int i = 0; i< (int) (StateGameObjects.size()); i++)
    {
        Text *ScrTxt = (Text*)StateGameObjects[i]->GetComponent(ComponentType::Text);
        if(ScrTxt != nullptr)
        {
            ScrTxt->SetColor(TextColor);
            break;
        }
    }  
    

    if(Input::Instance().KeyJustPressed(Key::Space))
    {
        _PopRequested = true;
        _EndMusic->Stop(500);
    }
    if((Input::Instance().KeyPressedDown(Key::Escape) || Input::Instance().QuitRequested())) 
	{
		_PopRequested = true;
		_QuitRequested = true;
        _EndMusic->Stop(500);
    }
}

void EndState::Render()
{
}


void EndState::Start()
{
    LoadAssets();
}

void EndState::Pause()
{

}

void EndState::Resume()
{

}
