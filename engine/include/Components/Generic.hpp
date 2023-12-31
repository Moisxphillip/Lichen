#ifndef LICHEN_GENERIC
#define LICHEN_GENERIC

#include <map>

#include "Components/Component.hpp"

class Generic : public Component
{
    private:
        std::string _Name;
        void(*_Render)(Generic*);
        void(*_Start)(Generic*);
        void(*_Update)(float, Generic*);

    public:
        bool Started;

        //Argument holders
        std::map<std::string, int> Int;
        std::map<std::string, float> Float;
        std::map<std::string, bool> Bool;
        std::map<std::string, void*> Ptr;
        float& Angle;
        Rectangle& Box;


        Generic(GameObject& Parent, std::string Name);
        void SetRender(void(*)(Generic*));
        void SetStart(void(*)(Generic*));
        void SetUpdate(void(*)(float, Generic*));
        void RequestDelete();

        std::string GetName();
        void Render();
        void Start();
        void Update(float Dt);

};
//Use this class for short-lived and simple Engine objects. For now, only tests!

#endif//LICHEN_GENERIC
