#ifndef SDL_CUSTOM_H_INCLUDED
#define SDL_CUSTOM_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2_gfxPrimitives.h>

#if SDL_MAJOR_VERSION != 2
#error SDL version is old!
#endif

enum
{
    SDL_TICK   = SDL_USEREVENT + 0,
    SDL_INIT   = SDL_USEREVENT + 1,
    SDL_REDRAW = SDL_USEREVENT + 2,
};

namespace Sdl
{

SDL_Color ConvertColor(Color c);

}

#endif // SDL_CUSTOM_H_INCLUDED
