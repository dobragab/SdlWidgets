#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void ColorBox::Paint(Surface& screen)
{
    if (!Visible)
        return;

    roundedRectangleColor(screen, location.x-1, location.y-1, location.x+_size.w, location.y+_size.h, 2, keret);
    boxColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, alapszin);
    rectangleColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, keretvilagos);
    boxColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, (uint32_t)color);

}

}
