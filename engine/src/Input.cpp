#include "../lib/Input.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Vector2.hpp"
#include "../lib/Tools.hpp"

//Set value for singleton class
Input* Input::_InputM = nullptr;

Input& Input::Instance()
{
    if(_InputM == nullptr) //Only creates a new Input if there's no other instance of the class currently running
    {
        _InputM = new Input();
    }
    return *_InputM;
}

Input::Input()
{
    if(_InputM != nullptr)//Report error if there is another instance working already
    {
        Error("Input::Input: Instance already exists");
        return;
    }
    else //Register pointer as current instance
    {
        _InputM = this;
    }

    //init mouse & keyboard states
    for(int i = 0; i<6; i++)
    {
        this->_MouseState[i] = false;
        this->_MouseUpdate[i] = 0;
    }
    for(int i = 0; i<416; i++)
    {
        this->_KeyState[i] = false;
        this->_KeyUpdate[i] = 0;
    }
    _MouseX = 0;
    _MouseY = 0;
    _UpdateCounter = 0;

    //will only change based on game or window requests
    this->_QuitRequested = false;

}

Input::~Input()
{
    if(_InputM != nullptr)
    {
        delete _InputM;
        _InputM = nullptr;
    }
}


void Input::Update()
{
    SDL_Event InputEvent;
    int KeySym;
	SDL_GetMouseState(&_MouseX, &_MouseY);//Get mouse coordinates
    _UpdateCounter++;

	while(SDL_PollEvent(&InputEvent))//Returns 1 if there's an event happening
    {
        switch(InputEvent.type)
        {
            case SDL_QUIT:
                _QuitRequested = true;
                break;

            case SDL_KEYDOWN:
                if(!InputEvent.key.repeat) //If there's no repetition (we can't mess the update counter)
                {
                    KeySym = ((InputEvent.key.keysym.sym <= 0x7F) ? InputEvent.key.keysym.sym : InputEvent.key.keysym.sym-0x3FFFFF81);//adjustment for fitting on key vector
                    _KeyState[KeySym] = true;
                    _KeyUpdate[KeySym] = _UpdateCounter;
                }                
                break;

            case SDL_KEYUP:
                KeySym = ((InputEvent.key.keysym.sym <= 0x7F) ? InputEvent.key.keysym.sym : InputEvent.key.keysym.sym-0x3FFFFF81);//adjustment for fitting on key vector
                _KeyState[KeySym] = false;
                _KeyUpdate[KeySym] = _UpdateCounter;
                break;

            case SDL_MOUSEBUTTONDOWN:
                _MouseState[InputEvent.button.button] = true;
                _MouseUpdate[InputEvent.button.button] = _UpdateCounter;
                break;

            case SDL_MOUSEBUTTONUP:
                _MouseState[InputEvent.button.button] = false;
                _MouseUpdate[InputEvent.button.button] = _UpdateCounter;
                break;

            default:
                break;
        }
    }
}

bool Input::QuitRequested()
{
    return _QuitRequested;
}

bool Input::KeyPress(int Key)
{
    int KeySym = ((Key <= 0x7F) ? Key : Key-0x3FFFFF81);
    return (_KeyState[KeySym] && (_KeyUpdate[KeySym] == _UpdateCounter));
}

bool Input::KeyRelease(int Key)
{
    int KeySym = ((Key <= 0x7F) ? Key : Key-0x3FFFFF81);
    return (!_KeyState[KeySym] && (_KeyUpdate[KeySym] == _UpdateCounter));
}

bool Input::IsKeyDown(int Key)
{
    return _KeyState[((Key <= 0x7F) ? Key : Key-0x3FFFFF81)];
}


bool Input::MousePress(int Switch)
{
    return (_MouseState[Switch] && _MouseUpdate[Switch] == _UpdateCounter);
}

bool Input::MouseRelease(int Switch)
{
    return (!_MouseState[Switch] && _MouseUpdate[Switch] == _UpdateCounter);
}

bool Input::IsMouseDown(int Switch)
{
    return _MouseState[Switch];
}

int Input::GetMouseX()
{
    return _MouseX + Engine::Instance().CurrentState().Cam.Position.x;
}

int Input::GetMouseY()
{
    return _MouseY + Engine::Instance().CurrentState().Cam.Position.y;
}

Vector2 Input::GetMouseVector2()
{
    return Vector2(GetMouseX(), GetMouseY());
}
