#include "../lib/ScreenFilter.hpp"
#include "../lib/Engine.hpp"
#include "../lib/Settings.hpp"


ScreenFilter::ScreenFilter(GameObject& GameObj, Color FilterColor)
: Component(GameObj)
{
    this->FilterColor = FilterColor;
    _FilterSurface = nullptr;
    Vector2 Dimensions = Engine::Instance().GetRenderSize();
    _FilterSurface = SDL_CreateRGBSurface(0,(int)Dimensions.x, (int)Dimensions.y, 32, 0,0,0,0);
}

ScreenFilter::~ScreenFilter()
{
    if(_FilterSurface != nullptr)
    {
        SDL_FreeSurface(_FilterSurface);
        _FilterSurface = nullptr;
    }
}

bool ScreenFilter::Is(std::string Type)
{
    return ("ScreenFilter" == Type);
}

void ScreenFilter::Render()
{
    // SDL_Texture* ToShow = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), _FilterSurface);
    // SDL_SetTextureBlendMode(ToShow, SDL_BLENDMODE_BLEND);
	// SDL_RenderCopy(Engine::Instance().GetRenderer(), ToShow, nullptr, nullptr);
	// SDL_DestroyTexture(ToShow);
}

void ScreenFilter::Update(float Dt)
{
    // SDL_SetSurfaceAlphaMod(_FilterSurface, 255-(int)(FilterColor.a*255));
    // SDL_FillRect(_FilterSurface, nullptr, FilterColor.ColorUint32());
}
		
		
		
