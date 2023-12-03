#include "Components/Filter.hpp"
#include "Core/Engine.hpp"

#include <iostream>
Filter::Filter(GameObject& GameObj, Color FilterColor)
: Component(GameObj)
{
    this->FilterColor = FilterColor;
    _FilterSurface = nullptr;
    _Dimensions = Engine::Instance().GetRenderSize();
    _Canvas = new FontHandler;
    _FilterSurface = SDL_CreateRGBSurface(0,(int)_Dimensions.x, (int)_Dimensions.y, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (_FilterSurface) 
    {
        SDL_FillRect(_FilterSurface, 0, SDL_MapRGBA(_FilterSurface->format, 255, 255, 255, 255));
    }
    _Canvas->CustomUpdate(_FilterSurface);
    _Type = ComponentType::Filter;
}

Filter::~Filter()
{
    delete _Canvas;
}

void Filter::Render()
{
    _Canvas->Render(Engine::Instance().GetRenderer(), Engine::Instance().GetWindow().GetProjection(),
        Parent.Box.Position()+_Dimensions/2.0f, Parent.Angle, Flip::N, FilterColor);
}
	
		
		
