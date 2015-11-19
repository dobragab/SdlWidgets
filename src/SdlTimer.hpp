#ifndef SDLTIMER_HPP_INCLUDED
#define SDLTIMER_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

typedef struct _SDL_TimerID *SDL_TimerID;
typedef uint32_t (*TimerCallback)(uint32_t interval, void *param);

class Timer
{
    SDL_TimerID id;
    void * param;
    uint32_t interval;
    TimerCallback callback;

public:
    Timer(uint32_t interval, TimerCallback callback, void * param = nullptr) :
        id{nullptr},
        param{param},
        interval{interval},
        callback{callback}
    { }

    void Start();

    void Finish();


};






}

#endif // SDLTIMER_HPP_INCLUDED
