#include "Components/Filter.hpp"
#include "Core/Engine.hpp"


Filter::Filter(GameObject& GameObj, Color FilterColor)
: Component(GameObj)
{
    this->FilterColor = FilterColor;
    _FilterSurface = nullptr;
    Vector2 Dimensions = Engine::Instance().GetRenderSize();
    _Canvas = new FontHandler;
    _FilterSurface = SDL_CreateRGBSurface(0,(int)Dimensions.x, (int)Dimensions.y, 32, 0xff,0xff,0xff,0);
    _Canvas->CustomUpdate(_FilterSurface);
    _Type = ComponentType::Filter;
    SDL_FreeSurface(_FilterSurface);
}

Filter::~Filter()
{
    delete _Canvas;
}

void Filter::Render()
{
    _Canvas->Render(Engine::Instance().GetRenderer(), Engine::Instance().GetWindow().GetProjection(),
        Parent.Box.Position(), Parent.Angle, Flip::N, FilterColor);
}
	
		
		
