#ifndef LICHEN_SCRFILTER
#define LICHEN_SCRFILTER

#include "SDL2/SDL_image.h"

#include "Components/Component.hpp"
#include "Tools/Color.hpp"
#include "Graphics/FontHandler.hpp"

class Filter : public Component
{
    private:
        SDL_Surface* _FilterSurface;
        FontHandler* _Canvas;

    public:
        Color FilterColor;
        Filter(GameObject& Parent, Color Colour);
        ~Filter();
        void Render();

};

#endif// LICHEN_SCRFILTER