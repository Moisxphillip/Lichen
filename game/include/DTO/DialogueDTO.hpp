#ifndef LICHEN_DIALOGUE_DTO
#define LICHEN_DIALOGUE_DTO

#include "Tools/JsonParser.hpp"
#include "Dialogue.hpp"
#include <queue>
#include <vector>

class DialogueDTO {
private:
    static std::queue<std::vector<JsonValue>> DialogueQueue;
    static Dialogue* GetDialoguesFromJson(JsonValue* DialogueArray, Dialogue* NextDialogue);

public:
    static Dialogue* ConvertfromJson(JsonValue* DialogueJson);
    static std::vector<std::string> GetLeftCharactersFileNameFromJson(JsonValue* DialogueJson);
    static std::vector<std::string> GetRightCharactersFileNameFromJson(JsonValue* DialogueJson);
};

#endif