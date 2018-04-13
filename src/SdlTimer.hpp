#ifndef SDLTIMER_HPP_INCLUDED
#define SDLTIMER_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

class TimerHandler
{
public:
    virtual void TimerTick(TimerEvent& ev) = 0;
    virtual ~TimerHandler() = default;
};


uint32_t TimerCallback(uint32_t interval, void *param);

class Timer
{
    using SDL_TimerID = int;

    SDL_TimerID id;
    uint32_t interval;
    TimerHandler * param;

public:
    Timer(uint32_t interval, TimerHandler * param);

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
