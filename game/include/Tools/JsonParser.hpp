#ifndef JSON_PARSER
#define JSON_PARSER

#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <fstream>
#include <queue>

class JsonValue;

typedef std::map<std::string, JsonValue*> Object;
// typedef std::variant<double, int, std::string, std::vector<JsonValue>> JsonValue; 
enum class JsonType{BOOL, DECIMAL, NUMERAL, STRING, ARRAY, OBJECT};

class JsonValue {
private:

    JsonType _Type;
    bool _BooleanValue;
    double _DecimalValue;
    int _IntValue;
    std::string _StringValue;
    std::vector<JsonValue*> _ArrayValue;
    Object _ObjectValue;

public:
    ~JsonValue(){
        if(_Type==JsonType::ARRAY)
        {
            for (auto Value = rbegin(_ArrayValue); Value != rend(_ArrayValue); ++Value) 
            {
                delete (*Value);
            }
            
            _ArrayValue.clear();
        }
        else if(_Type==JsonType::OBJECT)
        {
            for (auto Value = begin(_ObjectValue); Value != end(_ObjectValue); ++Value) 
            {
                delete Value->second;
            }
            
        }
    }
    JsonValue(double Value):_DecimalValue(Value), _Type(JsonType::DECIMAL){}
    JsonValue(int Value):_IntValue(Value), _Type(JsonType::NUMERAL){}
    JsonValue(std::string Value):_StringValue(Value), _Type(JsonType::STRING){}
    JsonValue(std::vector<JsonValue*> Value):_ArrayValue(Value), _Type(JsonType::ARRAY){}
    JsonValue(Object Value):_ObjectValue(Value), _Type(JsonType::OBJECT){}
    JsonValue(bool Value):_BooleanValue(Value), _Type(JsonType::BOOL){}

    int& AsInteger()
    {
        if(_Type != JsonType::NUMERAL)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: Integer"<<std::endl;
        }
        return _IntValue;
    }
    double&  AsDecimal()
    {
        if(_Type != JsonType::DECIMAL)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: Decimal."<<std::endl;
        }
        return _DecimalValue;
    }
    std::string&  AsString()
    {
        if(_Type != JsonType::STRING)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: String."<<std::endl;
        }
        return _StringValue;
    }
    std::vector<JsonValue*>& AsArray()
    {
        if(_Type != JsonType::ARRAY)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: Array."<<std::endl;
        }
        return _ArrayValue;
    }
    Object& AsObject()
    {
        if(_Type != JsonType::OBJECT)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: Object."<<std::endl;
        }
        return _ObjectValue;
    }
    bool& AsBoolean()
    {
        if(_Type != JsonType::BOOL)
        {
            std::cout<<"Warning: this json value does not hold this type. Called as: Bool."<<std::endl;
        }
        return _BooleanValue;
    }
};

class JsonParser {
private: 
    JsonParser();
    char _NextValidCharacter;
    bool _LastReadIsNumber;
    
    JsonValue* MatchField(std::fstream& File);
    char ReadNextValidCharacter(std::fstream& File);
    std::string ReadNextNCharacters(std::fstream& File, int n);

    JsonValue* ParseObject(std::fstream& File);
    JsonValue* ParseArray(std::fstream& File);
    JsonValue* ParseString(std::fstream& File);
    JsonValue* ParseNumber(std::fstream& File);

public:
    static JsonValue* LoadJson(std::string FileName);
    
};

#endif