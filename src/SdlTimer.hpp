#ifndef SDLTIMER_HPP_INCLUDED
#define SDLTIMER_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

typedef int SDL_TimerID;

uint32_t TimerCallback(uint32_t interval, void *param);

class Timer
{
    SDL_TimerID id;
    uint32_t interval;
    void * param;

public:
    Timer(uint32_t interval, void * param);

    Timer(Timer&& old);
    Timer& operator=(Timer&& old);

    Timer(const Timer& old) = delete;
    Timer& operator=(const Timer& old) = delete;

    ~Timer();

    void Start();
    void Finish();

    bool IsRunning();
};

}

#endif // SDLTIMER_HPP_INCLUDED
