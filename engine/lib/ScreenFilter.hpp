#ifndef LICHEN_SCRFILTER
#define LICHEN_SCRFILTER

#include "SDL2/SDL_image.h"

#include "Component.hpp"
#include "Color.hpp"

class ScreenFilter : public Component
{
    private:
        SDL_Surface* _FilterSurface;

    public:
        Color FilterColor;
        ScreenFilter(GameObject&, Color);
        ~ScreenFilter();

        bool Is(std::string);
        void Render();
        void Update(float);

};

#endif// LICHEN_SCRFILTER