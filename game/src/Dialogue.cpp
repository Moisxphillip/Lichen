
#include "Dialogue.hpp"
#include "Tools/JsonParser.hpp"
#include "DTO/DialogueDTO.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"

#include <map>
#include <cmath>


DialogueManager::DialogueManager(GameObject& Parent, std::string JsonFileName):
    Component(Parent), 
    _UsedTextsCounter(0),
    _StartDialogue(nullptr),
    _NextDialogue(nullptr),
    _CurrentDialogue(nullptr)
    {
    JsonValue * Json = JsonParser::LoadJson(JsonFileName);
    _StartDialogue = DialogueDTO::ConvertfromJson(Json);

    std::vector<std::string> LeftSpriteFileNames =  DialogueDTO::GetLeftCharactersFileNameFromJson(Json);

    for(auto FileName : LeftSpriteFileNames)
    {
        Sprite* Char = new Sprite(Parent, FileName);
        Char->SetFlip(Flip::H);
        AddLeftCharacterSprite(Char);
    }

    std::vector<std::string> RightSpriteFileNames =  DialogueDTO::GetLeftCharactersFileNameFromJson(Json);

    for(auto FileName : RightSpriteFileNames)
    {
        AddRightCharacterSprite(new Sprite(Parent, FileName));
    }
    

    delete Json;
}

DialogueManager::~DialogueManager(){
    for (auto Sprite = rbegin(_RightCharacterSprites); Sprite != rend(_RightCharacterSprites); ++Sprite) 
    {
        delete (*Sprite);
    }
    
    _RightCharacterSprites.clear();

    for (auto Sprite = rbegin(_LeftCharacterSprites); Sprite != rend(_LeftCharacterSprites); ++Sprite) 
    {
        delete (*Sprite);
    }
    
    _LeftCharacterSprites.clear();

    for (auto TextLine = rbegin(_Texts); TextLine != rend(_Texts); ++TextLine) 
    {
        delete (*TextLine);
    }
    
    _Texts.clear();

    delete _StartDialogue;
}


void DialogueManager::Update(float Dt)
{
    // Parent.Box.SetPosition(Camera::Position()+Vector2(0,484));
    _CurrentDialogue->Update(*this, Dt);
}

void DialogueManager::LateUpdate(float Dt){
    if(_NextDialogue != nullptr){
        _CurrentDialogue = _NextDialogue;
        _NextDialogue = nullptr;
    }

    if(_CurrentDialogue->HasEnded)
    {
        std::cout<<_CurrentDialogue->HasEnded<<std::endl;
    }
    while(_CurrentDialogue->HasEnded && _CurrentDialogue->NextDialogue != nullptr){
        _CurrentDialogue = _CurrentDialogue->NextDialogue;
    }
}

void DialogueManager::Render()
{
    _BackgroundImage->Render();
    _CurrentDialogue->Render(*this);
}

#include "Components/CameraFollower.hpp"
void DialogueManager::Start()
{
    _CurrentDialogue = _StartDialogue;
    Parent.AddComponent(new CameraFollower(Parent));
    _BackgroundImage = new Sprite(Parent, "res/img/back-dialogue.png");
}

void DialogueManager::AddLeftCharacterSprite(Sprite* Character){
    _LeftCharacterSprites.emplace_back(Character);
}

void DialogueManager::AddRightCharacterSprite(Sprite* Character){
    _RightCharacterSprites.emplace_back(Character);
}

Sprite* DialogueManager::GetLeftCurrentCharacter(int SpriteSheetIdx){
    if(SpriteSheetIdx >= _LeftCharacterSprites.size() || SpriteSheetIdx < 0)
    {
        return nullptr;
    }

    return _LeftCharacterSprites[SpriteSheetIdx];
}

Sprite* DialogueManager::GetRightCurrentCharacter(int SpriteSheetIdx){
    if(SpriteSheetIdx >= _RightCharacterSprites.size() || SpriteSheetIdx < 0)
    {
        return nullptr;
    }

    return _RightCharacterSprites[SpriteSheetIdx];
}

void DialogueManager::SetNextDialogue(Dialogue* NextDialogue){
    _NextDialogue = NextDialogue;
}

void DialogueManager::WriteText(int idx, std::string TextLine, Vector2 Position, TextAlignment Alignment, Color TextColor){
    if(idx > _Texts.size())
    {
        Error("DialogueManager::WriteText: Text index out of range.");
        return;
        
    }
    else if (idx == _Texts.size())
    {
        _Texts.emplace_back(new Text(Parent, "./res/ttf/Caviar.ttf", 20, TextStyle::SOLID, TextLine, TextColor));
    }
    else
    {
        _Texts[idx]->SetText(TextLine);
        _Texts[idx]->SetColor(TextColor);
    }

    _Texts[idx]->SetAlignment(Alignment);
    _Texts[idx]->Render(Position);
}


// _________________________________________________________Dialogue_________________________________________________________

Dialogue::Dialogue():NextDialogue(nullptr), HasEnded(false){}

Dialogue::~Dialogue(){
    delete NextDialogue;
}

Dialogue::Dialogue(Dialogue* NextDialogue): NextDialogue(NextDialogue){}

void Dialogue::Update(DialogueManager& Dm, float Dt){}

void Dialogue::Render(DialogueManager& Dm){}



// _________________________________________________________DialogueText_________________________________________________________

DialogueText::DialogueText(): Dialogue(), _HasWrittenText(false), _ElapsedTime(0){}

DialogueText::DialogueText(std::string TextLine, Color TextColor, TextAlignment Alignment, int LeftFocalCharacter,int RightFocalCharacter, int LeftSpriteSheet, int RightSpriteSheet, Dialogue* NextDialogue):
    _TextLine(TextLine), 
    _TextColor(TextColor), 
    _Alignment(Alignment), 
    _LeftFocalCharacter(LeftFocalCharacter), 
    _RightFocalCharacter(RightFocalCharacter), 
    _LeftSpriteSheet(LeftSpriteSheet), 
    _RightSpriteSheet(RightSpriteSheet), 
    Dialogue(NextDialogue),
    _HasWrittenText(false),
    _ElapsedTime(0)
    {}

DialogueText::~DialogueText(){}

void DialogueText::Update(DialogueManager& Dm,  float Dt)
{
    Input& Input = Input::Instance();

    if(!_HasWrittenText)
    {
        _ElapsedTime += Dt;

        if(_ElapsedTime >= SECONDS_PER_LETTER*_TextLine.size())
        {
            _ElapsedTime = SECONDS_PER_LETTER*_TextLine.size();
            _HasWrittenText = true;
        }
    }

    if(Input.KeyJustReleased(Key::Space)){
        if(!_HasWrittenText)
        {
            _HasWrittenText = true;
            _ElapsedTime = SECONDS_PER_LETTER*_TextLine.size();
        }
        else
        {
            if(NextDialogue)
            {
                Dm.SetNextDialogue(NextDialogue);
                Reset();
            }
            else
            {
                Dm.Parent.RequestDelete();
            }
            
        }
    }
}

void DialogueText::Render(DialogueManager& Dm)
{
    
    Vector2 ParentPosition = Dm.Parent.Box.Position();

    std::cout<<_LeftFocalCharacter<<std::endl;
    Sprite * LeftCharacter = Dm.GetLeftCurrentCharacter(_LeftFocalCharacter);
    if(LeftCharacter != nullptr)
    {
        Vector2 LeftPos = ParentPosition+Vector2(-180,0);
        // LeftCharacter->SetFrame(LeftFocalCharacter);
        LeftCharacter->Render(LeftPos.x, LeftPos.y);
    }

    std::cout<<_RightFocalCharacter<<std::endl;
    Sprite * RightCharacter = Dm.GetRightCurrentCharacter(_RightFocalCharacter);
    if(RightCharacter != nullptr)
    {
        Vector2 RightPos = ParentPosition+Vector2(800,0);
        // RightCharacter->SetFrame(RightFocalCharacter);
        RightCharacter->Render(RightPos.x, RightPos.y);
    }

    std::string TextToWrite = " ";

    if(((int)(_ElapsedTime/SECONDS_PER_LETTER))>1)
    {
        TextToWrite= _TextLine.substr(0,ceil(_ElapsedTime/SECONDS_PER_LETTER));
    }

    Vector2 TextPos = ParentPosition;

    switch(_Alignment)
    {
        case TextAlignment::LEFT:
            TextPos += Vector2(300, 80);
            break;
        case TextAlignment::RIGHT:
            TextPos += Vector2(700,80);
            break;
        default:
            TextPos += Vector2(640,80);
            break;
    }

    Dm.WriteText(0, TextToWrite, TextPos, _Alignment, _TextColor);
}

void DialogueText::Reset(){
    _ElapsedTime = 0;
    _HasWrittenText = false;
}

// _________________________________________________________DialogueAnswers_________________________________________________________

DialogueAnswers::DialogueAnswers(): Dialogue(){}

DialogueAnswers::DialogueAnswers(std::string Question, Dialogue* NextDialogue): 
    _Question(Question),
    _SelectedAnswerIdx(0),
    Dialogue(NextDialogue){}

DialogueAnswers::~DialogueAnswers(){
    
    for (auto Answer = rbegin(_AnswerOptions); Answer != rend(_AnswerOptions); ++Answer) 
    {
        delete (*Answer).DialogueOption;
    }
    
    _AnswerOptions.clear();
}   

void DialogueAnswers::Update(DialogueManager& Dm,  float Dt)
{
    Input& Input = Input::Instance();


    if(Input.KeyJustReleased(Key::Down))
    {
        _SelectedAnswerIdx = (_SelectedAnswerIdx + 1) % _AnswerOptions.size();
    }

    if(Input.KeyJustReleased(Key::Up))
    {
        _SelectedAnswerIdx = (_SelectedAnswerIdx - 1) % _AnswerOptions.size();
    }
    if(Input.KeyJustReleased(Key::Space))
    {
        _AnswerOptions[_SelectedAnswerIdx].AlreadyChosen = true;
        if(_AnswerOptions[_SelectedAnswerIdx].FinalAnswer)
        {
            HasEnded = true;
        }
        Dm.SetNextDialogue(_AnswerOptions[_SelectedAnswerIdx].DialogueOption);
        
    }
}

void DialogueAnswers::Render(DialogueManager& Dm)
{
    Vector2 BasePos = Dm.Parent.Box.Position()+Vector2(600, 30);
    Dm.WriteText(0, _Question, BasePos,TextAlignment::CENTER, Color("#FFFFFF"));

    BasePos+=Vector2(0,60);

    for(int i = 0; i< _AnswerOptions.size(); i++){
        Color TextColor;
        if(i == _SelectedAnswerIdx)
        {
            TextColor = Color("#65ff4a");
        }
        else if(_AnswerOptions[i].FinalAnswer)
        {
            TextColor = Color("#f5d927");
        }
        else if(_AnswerOptions[i].AlreadyChosen )
        {
            TextColor = Color("#7a7a7a");
        }
        else 
        {
            TextColor = Color("#FFFFFF");
        }

        Dm.WriteText(i+1, _AnswerOptions[i].Answer, BasePos, TextAlignment::CENTER, TextColor);
        BasePos += Vector2(0,30);
    }

}

void DialogueAnswers::AddOption(Dialogue* Dialogue, std::string Answer, bool FinalAnswer)
{
    _AnswerOptions.emplace_back(AnswerOption{Answer, Dialogue, false, FinalAnswer});
}