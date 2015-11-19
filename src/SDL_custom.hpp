#ifndef SDL_CUSTOM_H_INCLUDED
#define SDL_CUSTOM_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_gfxPrimitives.h>

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
