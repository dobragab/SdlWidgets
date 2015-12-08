#ifndef SDL_CUSTOM_H_INCLUDED
#define SDL_CUSTOM_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#if SDL_MAJOR_VERSION != 2
#error SDL version is old!
#endif

#if defined(SDL_GFXPRIMITIVES_MAJOR) || defined(SDL2_GFXPRIMITIVES_MAJOR)
#error Do not include SDL_gfx or SDL2_gfx here! They could get confused!
#endif

constexpr int IMG_INIT_EVERYTHING = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

enum
{
    SDL_TICK   = SDL_USEREVENT + 0,
    SDL_INIT   = SDL_USEREVENT + 1,
    SDL_REDRAW = SDL_USEREVENT + 2,
};

namespace Sdl
{

SDL_Color ConvertColor(Color c);

SDL_RWops * SDL_RWFromFileToMemory(const char * filename, const char * mode, void *& bytebuffer);

}

#endif // SDL_CUSTOM_H_INCLUDED
