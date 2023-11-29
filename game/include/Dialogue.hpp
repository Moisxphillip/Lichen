#ifndef LICHEN_DIALOGUE
#define LICHEN_DIALOGUE

#include "Tools/EventChain.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include <map>

#define SECONDS_PER_LETTER 0.1

class DialogueManager;

enum TextPosition{TEXT_LEFT, TEXT_RIGHT, TEXT_CENTER};

class Dialogue {
public:
    Dialogue* NextDialogue;

    Dialogue();
    ~Dialogue();
    Dialogue(Dialogue* NextDialogue);   

    virtual void Update(DialogueManager& Dm, float Dt);
    virtual void Render(DialogueManager& Dm);

    bool HasEnded;
};

class DialogueText: public Dialogue {
private:
    bool _HasWrittenText;
    float _ElapsedTime;
    std::string _TextLine;
    Color _TextColor;
    TextAlignment _Alignment;
    int _LeftFocalCharacter;
    int _LeftSpriteSheet;
    int _RightFocalCharacter;
    int _RightSpriteSheet;

public:
    DialogueText();
    ~DialogueText();
    DialogueText(std::string TextLine, Color TextColor, TextAlignment Alignment, int LeftFocalCharacter, int RightFocalCharacter, int LeftSpriteSheet, int RightSpriteSheet, Dialogue* NextDialogue);

    void Update(DialogueManager& Dm, float Dt);
    void Render(DialogueManager& Dm);
    void Reset();
};

class DialogueAnswers: public Dialogue {
private:
    struct AnswerOption {
        std::string Answer;
        Dialogue* DialogueOption;
        bool AlreadyChosen;
        bool FinalAnswer;
    };

    std::vector<AnswerOption> _AnswerOptions;
    std::string _Question;
    int _SelectedAnswerIdx;

public:
    DialogueAnswers();
    DialogueAnswers(std::string _Question, Dialogue* NextDialogue);
    ~DialogueAnswers();
    void AddOption(Dialogue* Dialogue, std::string Answer, bool FinalAnswer);

    void Update(DialogueManager& Dm,  float Dt);
    void Render(DialogueManager& Dm);
};

class DialogueManager: public Component   {
private:
    Dialogue* _StartDialogue;
    Dialogue* _CurrentDialogue;
    Dialogue* _NextDialogue;
    std::vector<Sprite*> _LeftCharacterSprites;
    std::vector<Sprite*> _RightCharacterSprites;
    std::vector<Text*> _Texts;
    Sprite* _BackgroundImage;
    int _UsedTextsCounter;
    int _LeftFocalCharachterIdx;
    int _RightFocalCharachterIdx;

public:
    DialogueManager(GameObject& Parent, std::string JsonFileName);
    ~DialogueManager();
    void AddLeftCharacterSprite(Sprite* Character);
    void AddRightCharacterSprite(Sprite* Character);
    Sprite * GetLeftCurrentCharacter(int SpriteSheetIdx);
    Sprite * GetRightCurrentCharacter(int SpriteSheetIdx);

    void SetNextDialogue(Dialogue* NextDialogue);
    void WriteText(int idx, std::string TextLine, Vector2 Position, TextAlignment Alignment, Color TextColor);

    // virtual ~Component();
    void Update(float Dt);
    virtual void LateUpdate(float Dt);
    void Render();
    void Start();
    // virtual ComponentType Type();
};



#endif