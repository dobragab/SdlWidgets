#include <cstdio>

#include "Sdl.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void PushEvent(uint8_t type, void * data1, void * data2)
{
    SDL_Event ev;
    ev.type = type;
    ev.user.code = 0;
    ev.user.data1 = data1;
    ev.user.data2 = data2;

    SDL_PushEvent(&ev);
}

exception::exception() :
    std::runtime_error(SDL_GetError())
{ }

static void Quit()
{
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void Init()
{
    bool result =
        SDL_Init(SDL_INIT_EVERYTHING) == 0 &&
        TTF_Init() == 0 &&
        IMG_Init(IMG_INIT_EVERYTHING) == IMG_INIT_EVERYTHING;

    if (!result)
        throw Sdl::exception();

    atexit(Quit);

#if defined(__WIN32__) && defined(DEBUG)
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

}

}
