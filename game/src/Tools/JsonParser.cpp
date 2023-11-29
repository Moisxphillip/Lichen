
#include "Tools/JsonParser.hpp"
#include "Tools/Tools.hpp"
#include <regex>


JsonParser::JsonParser():_LastReadIsNumber(false){}

JsonValue* JsonParser::LoadJson(std::string FileName)
{
    std::fstream File;
    std::string Token;
    JsonParser Parser = JsonParser();

    File.open(FileName, std::ios::in);
    
    if(std::getline(File, Token, '{'))
    {
        JsonValue* ReadJson = Parser.ParseObject(File);
        File.close();
        
        return ReadJson;
    }

    Error("JsonParser::LoadJson: Couldn't find json start. ");
    File.close();
    return new JsonValue(Object{});
}


JsonValue* JsonParser::MatchField(std::fstream& File)
{
    ReadNextValidCharacter(File);

    if(_NextValidCharacter == '{') 
    {
        return ParseObject(File);
    }
    else if (_NextValidCharacter == '[')
    {
        return ParseArray(File);
    }
    else if(_NextValidCharacter == '"')
    {
        return ParseString(File);
    }
    else if(isdigit(_NextValidCharacter) || _NextValidCharacter == '-' || _NextValidCharacter == '+')
    {
        return ParseNumber(File);
    }
    else if(_NextValidCharacter == 't')
    {
        ReadNextNCharacters(File, 3);
        return new JsonValue(true);
    }
    else if(_NextValidCharacter == 'f')
    {
        ReadNextNCharacters(File, 4);
        return new JsonValue(false);
    }
    else
    {
        Error("JsonParser::MatchField: Couldn't match pattern. Reading: "+_NextValidCharacter);
        return new JsonValue(Object{});
    }
}

JsonValue* JsonParser::ParseObject(std::fstream& File)
{
    JsonValue* ObjectValue = new JsonValue(Object{});

    _NextValidCharacter = ',';

    while(_NextValidCharacter == ',')
    {
        ReadNextValidCharacter(File);

        JsonValue* Identifier = ParseString(File);

        if(!ReadNextValidCharacter(File) == ':')
        {
            Error("JsonParser::LoadJson ParseObject: Not an object structure.");
            return new JsonValue(Object{});
        }

        
        ObjectValue->AsObject()[Identifier->AsString()] = MatchField(File);
        delete Identifier;
        

        if(!_LastReadIsNumber)
        {
            ReadNextValidCharacter(File);
        }
        else 
        {
            _LastReadIsNumber = false;
        }
    };


    if(_NextValidCharacter == '}')
    {
        return ObjectValue;
    }
    else
    {
        delete ObjectValue;
        Error("JsonParser::LoadJson ParseObject: Couldn't find object's end.");
        return new JsonValue(Object{});
    }
}


JsonValue* JsonParser::ParseArray(std::fstream& File)
{
    JsonValue* ArrayValue = new JsonValue(std::vector<JsonValue*>());

    do
    {
        ArrayValue->AsArray().emplace_back(MatchField(File));
        
        if(!_LastReadIsNumber)
        {
            ReadNextValidCharacter(File);
        }
        else 
        {
            _LastReadIsNumber = false;
        }

    }
    while(_NextValidCharacter == ',');
    
    
    if(_NextValidCharacter==']')
    {   
        return ArrayValue;
    }
    else
    {
        delete ArrayValue;
        Error("JsonParser::ParseArray: Couldn't find array's end.");
        return new JsonValue(std::vector<JsonValue*>());
    }

}
JsonValue* JsonParser::ParseString(std::fstream& File){
    std::string Token;

    if(std::getline(File, Token, '"'))
    {
        return new JsonValue(Token);
    }
    else
    {
        Error("JsonParser::LoadJson ParseString: Couldn't find string end");
        return new JsonValue("");
    }

}

JsonValue* JsonParser::ParseNumber(std::fstream& File){
    std::regex FloatRegex = std::regex("[+-]?[0-9]*[.][0-9]+");
    std::regex IntRegex = std::regex("^[+-]?\\d*$");
    
    std::string Token = "";
    do
    {
        Token+= _NextValidCharacter;
        File >> _NextValidCharacter;
    }
    while( isdigit(_NextValidCharacter) || _NextValidCharacter == '.');

    _LastReadIsNumber = true;

    if(std::regex_match(Token, FloatRegex))
    {
        return new JsonValue(atof(Token.c_str()));
    }
    else if(std::regex_match(Token, IntRegex))
    {
        return new JsonValue(atoi(Token.c_str()));
    }
    else  
    {
        Error("Error JsonParser::LoadJson ParseNumber: Not a number");
        return 0;
    }

}

char JsonParser::ReadNextValidCharacter(std::fstream& File)
{
    char c;
    do{
        File >> c;
    }while((c == ' '  || c == '\n') && !File.eof());
    _NextValidCharacter = c;
    return c;
}

std::string JsonParser::ReadNextNCharacters(std::fstream& File, int n)
{
    char c;
    std::string result;
    for(int i =0 ; i< n && !File.eof(); i++){
        File >> c;
        result += c;
    }
    return result;
}


