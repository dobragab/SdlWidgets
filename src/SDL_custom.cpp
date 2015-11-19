#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

SDL_Color ConvertColor(Color c)
{
    SDL_Color result;

    result.r = c.r;
    result.g = c.g;
    result.b = c.b;
    result.unused = c.a;

    return result;
}

}
