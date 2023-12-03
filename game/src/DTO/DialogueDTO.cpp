#include "DTO/DialogueDTO.hpp"
#include "Tools/Tools.hpp"
#include <ctype.h>


Dialogue* DialogueDTO::ConvertfromJson(JsonValue* DialogueJson)
{
    if(DialogueJson->AsObject().count("Dialogues")!=0)
    {
        return GetDialoguesFromJson(DialogueJson->AsObject()["Dialogues"], nullptr);
    }
    else
    {
        Error("DialogueDTO::ConvertFromJson: Couldn't find 'Dialogues' field");
    }

    return nullptr;
}

Dialogue* DialogueDTO::GetDialoguesFromJson(JsonValue* DialogueArray, Dialogue* NextDialogue) 
{
    
    for (auto DialogueObject = rbegin(DialogueArray->AsArray()); DialogueObject != rend(DialogueArray->AsArray()); ++DialogueObject)
    {


        if((*DialogueObject)->AsObject().count("Question")!=0)
        {
            std::string Question = (*DialogueObject)->AsObject()["Question"]->AsString();
            DialogueAnswers* DialogueAnswerNode = new DialogueAnswers(Question, NextDialogue);

            if((*DialogueObject)->AsObject().count("Answers")!=0)
            {
                for(auto Answer : (*DialogueObject)->AsObject()["Answers"]->AsArray())
                {   
                    if(Answer->AsObject().count("Dialogues")!=0)
                    {
                        auto AnswerText = Answer->AsObject().count("Text")!=0 ?  Answer->AsObject()["Text"]->AsString() : "";
                        bool IsFinalAnswer = Answer->AsObject().count("FinalAnswer")!=0 ?  Answer->AsObject()["FinalAnswer"]->AsBoolean() : false;
                        Dialogue* Option = GetDialoguesFromJson(Answer->AsObject()["Dialogues"], DialogueAnswerNode);

                        DialogueAnswerNode->AddOption(Option, AnswerText, IsFinalAnswer);
                    }
                }
            }
            NextDialogue = DialogueAnswerNode;
        }


        else if((*DialogueObject)->AsObject().count("Text")!=0)
        {
            std::string Text = (*DialogueObject)->AsObject().count("Text")!=0 ?  (*DialogueObject)->AsObject()["Text"]->AsString() : "";
            int LeftFocalCharacter  = (*DialogueObject)->AsObject().count("LeftFocalSprite")!=0 ? (*DialogueObject)->AsObject()["LeftFocalSprite"]->AsInteger() : -1;
            int RightFocalCharacter  =  (*DialogueObject)->AsObject().count("RightFocalSprite")!=0 ?  (*DialogueObject)->AsObject()["RightFocalSprite"]->AsInteger() : -1;
            int LeftSpriteSheet  = (*DialogueObject)->AsObject().count("LeftSpriteSheet")!=0 ? (*DialogueObject)->AsObject()["LeftSpriteSheet"]->AsInteger() : -1;
            int RightSpriteSheet  =  (*DialogueObject)->AsObject().count("RightSpriteSheet")!=0 ?  (*DialogueObject)->AsObject()["RightSpriteSheet"]->AsInteger() : -1;
            std::string ColorText  = (*DialogueObject)->AsObject().count("TextColor")!=0 ?  (*DialogueObject)->AsObject()["TextColor"]->AsString() : "";
            std::string Position  = (*DialogueObject)->AsObject().count("TextPosition")!=0 ? (*DialogueObject)->AsObject()["TextPosition"]->AsString() : "";

            // TODO to lower
            TextAlignment Pos = TextAlignment::CENTER;
            if ( Position == "Left") Pos = TextAlignment::LEFT;
            if ( Position == "Right") Pos = TextAlignment::RIGHT;

            NextDialogue = new DialogueText(Text, Color(ColorText), Pos, LeftFocalCharacter, RightFocalCharacter, LeftSpriteSheet, RightSpriteSheet, NextDialogue);
        }
        else 
        {
            Error("DialogueDTO::ConvertFromJson: GetDialoguesFromJson couldn't find any recognizable field.");
            return nullptr;
        }


    }

    return NextDialogue;

}

std::vector<std::string> DialogueDTO::GetLeftCharactersFileNameFromJson(JsonValue* DialogueJson)
{
    std::vector<std::string> FileNames = std::vector<std::string>();

    if(DialogueJson->AsObject().count("LeftSideSpriteSheets")!=0)
    {
        for (auto FileName = begin(DialogueJson->AsObject()["LeftSideSpriteSheets"]->AsArray()); FileName != end(DialogueJson->AsObject()["LeftSideSpriteSheets"]->AsArray()); ++FileName)
        {
            FileNames.emplace_back((*FileName)->AsString());
        }
    }

    return FileNames;
}

std::vector<std::string> DialogueDTO::GetRightCharactersFileNameFromJson(JsonValue* DialogueJson)
{
    std::vector<std::string> FileNames = std::vector<std::string>();

    if(DialogueJson->AsObject().count("RightSideSpriteSheets")!=0)
    {
        for (auto FileName = begin(DialogueJson->AsObject()["RightSideSpriteSheets"]->AsArray()); FileName != end(DialogueJson->AsObject()["RightSideSpriteSheets"]->AsArray()); ++FileName)
        {
            FileNames.emplace_back((*FileName)->AsString());
        }
    }

    return FileNames;
}

// Dialogue* DialogueDTO::MatchDialogueTypeFromField(Dialogue*){
//     std::vector<JsonValue> JsonArray = DialogueDTO::DialogueQueue.front();
//     Object fields = JsonArray[0].GetAsObject();

//     if(fields["Question"]){
//         GetAnswerDialogueFromField();
//     }else if(fields["Dialogues"]){
//         GetTextDialogueFromField();
//     }

// }


// Dialogue* DialogueDTO::GetTextDialogueFromField(Dialogue*){
//     std::vector<JsonValue> JsonArray = DialogueDTO::DialogueQueue.front();
//     Object fields = JsonArray[0].GetAsObject();

//     Dialogue* NextDialogue;
//     if(fields.size()>2)
//         NextDialogue = ;
//     else 
//         NextDialogue = nullptr;


//     new DialogueText(
//         fields["Text"].GetAsString(),
//         fields["Color"].GetAsString(),
//         fields["Position"].GetAsString(),
//         fields["FocalCharacher"].GetAsInteger(),
//         NextDialogue
//     );

//     fields.erase(0);

//     if vetor length+1? null
//         pop
//     if pilha vaiz return
     
// }

// Dialogue* DialogueDTO::GetAnswerDialogueFromFieldDialogue(){
    


//     new DialogueAnswers(
//         fields["Question"].GetAsString()
        
//         )
//         new anwser
//         if(< legth)
//             dialogue next recebe vecotr i+1
//         pegar question
//         for dos filhos com o next no map
//             sobre na pilhar
//     if vetor length+1? null
//         pop
//     if pilha vaiz return

// }