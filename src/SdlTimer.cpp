#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

uint32_t TimerCallback(uint32_t interval, void *param)
{
    SDL_Event ev;
    ev.user.code = 0;
    ev.user.data1 = param;
    ev.user.data2 = nullptr;
    ev.user.type = SDL_TICK;
    SDL_PushEvent(&ev);

    return interval;
}

Timer::Timer(uint32_t interval, void * param) :
    id{0},
    interval{interval},
    param{param}
{ }

Timer::Timer(Timer&& old) :
    id{old.id},
    interval{old.interval},
    param{old.param}
{
    old.id = 0;
}

Timer& Timer::operator=(Timer&& old)
{
    if (this != &old)
    {
        if (id != 0)
            SDL_RemoveTimer(id);

        id = old.id;
        interval = old.interval;
        param = old.param;

        old.id = 0;
    }
    return *this;
}

Timer::~Timer()
{
    Finish();
}

void Timer::Start()
{
    if (id == 0)
    {
        id = SDL_AddTimer(interval, TimerCallback, param);
        if (id == 0)
            throw Sdl::exception();
    }
}

void Timer::Finish()
{
    if (id != 0)
    {
        SDL_RemoveTimer(id);
        id = 0;
    }
}

bool Timer::IsRunning()
{
    return !!id;
}

}

