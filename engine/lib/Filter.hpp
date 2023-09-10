#ifndef LICHEN_SCRFILTER
#define LICHEN_SCRFILTER

#include "SDL2/SDL_image.h"

#include "Component.hpp"
#include "Color.hpp"
#include "FontHandler.hpp"

class Filter : public Component
{
    private:
        SDL_Surface* _FilterSurface;
        FontHandler* _Canvas;

    public:
        Color FilterColor;
        Filter(GameObject&, Color);
        ~Filter();
        void Render();

};

#endif// LICHEN_SCRFILTER