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


void Init()
{
    int result = SDL_Init(SDL_INIT_EVERYTHING);

    if (result < 0)
        throw Sdl::exception();

    atexit(SDL_Quit);

#if defined(__WIN32__) && defined(DEBUG)
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

    TTF_Init();
    SDL_EnableUNICODE(true);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

}
