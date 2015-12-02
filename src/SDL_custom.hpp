#ifndef SDL_CUSTOM_H_INCLUDED
#define SDL_CUSTOM_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#if SDL_MAJOR_VERSION != 2
#error SDL version is old!
#endif

#define SDL2_GFX_ERROR \
#error SDL2_GFX is buggy, Color versions do not work properly. Please use RGBA equivalents instead.
// FUCK YOU SDL2_GFX
#define pixelColor                  SDL2_GFX_ERROR
#define hlineColor                  SDL2_GFX_ERROR
#define vlineColor                  SDL2_GFX_ERROR
#define rectangleColor              SDL2_GFX_ERROR
#define roundedRectangleColor       SDL2_GFX_ERROR
#define boxColor                    SDL2_GFX_ERROR
#define roundedBoxColor             SDL2_GFX_ERROR
#define lineColor                   SDL2_GFX_ERROR
#define aalineColor                 SDL2_GFX_ERROR
#define thickLineColor              SDL2_GFX_ERROR
#define circleColor                 SDL2_GFX_ERROR
#define arcColor                    SDL2_GFX_ERROR
#define aacircleColor               SDL2_GFX_ERROR
#define filledCircleColor           SDL2_GFX_ERROR
#define ellipseColor                SDL2_GFX_ERROR
#define aaellipseColor              SDL2_GFX_ERROR
#define filledEllipseColor          SDL2_GFX_ERROR
#define pieColor                    SDL2_GFX_ERROR
#define filledPieColor              SDL2_GFX_ERROR
#define trigonColor                 SDL2_GFX_ERROR
#define aatrigonColor               SDL2_GFX_ERROR
#define filledTrigonColor           SDL2_GFX_ERROR
#define polygonColor                SDL2_GFX_ERROR
#define aapolygonColor              SDL2_GFX_ERROR
#define filledPolygonColor          SDL2_GFX_ERROR
#define bezierColor                 SDL2_GFX_ERROR
#define characterColor              SDL2_GFX_ERROR
#define stringColor                 SDL2_GFX_ERROR

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
