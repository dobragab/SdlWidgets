#ifndef SDLEVENT_HPP_INCLUDED
#define SDLEVENT_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{


class Event
{
    bool handled = false;

public:
    inline void Done()
    {
        handled = true;
    }
    inline bool IsDone()
    {
        return handled;
    }
};

struct KeyboardEvent : public Event
{
    uint16_t modifiers; // SDLMod
    uint16_t keysym;    // SDLKey
    uint16_t unicode;

    KeyboardEvent(uint16_t modifiers, uint16_t keysym, uint16_t unicode) :
        modifiers{modifiers},
        keysym{keysym},
        unicode{unicode}
    { }
};

struct MouseClickEvent : public Event
{
    uint8_t button; // The mouse button index (SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT)
    bool down;
    Point p;

    MouseClickEvent(uint8_t button, bool down, Point p) :
        button{button},
        down{down},
        p{p}
    { }

    MouseClickEvent(uint8_t button, bool down, int16_t x, int16_t y) :
        button{button},
        down{down},
        p{x, y}
    { }

};
struct MouseMoveEvent : public Event
{
    uint8_t state; // button states
    Point p;
    int16_t xrel, yrel;

    MouseMoveEvent(uint8_t state, Point p, int16_t xrel, int16_t yrel) :
        state{state},
        p{p},
        xrel{xrel},
        yrel{yrel}
    { }

    MouseMoveEvent(uint8_t state, int16_t x, int16_t y, int16_t xrel, int16_t yrel) :
        state{state},
        p{x, y},
        xrel{xrel},
        yrel{yrel}
    { }

};

struct TimerEvent : public Event
{
    int code;
    void * data1;
    void * data2;

    TimerEvent(int code, void * data1, void * data2) :
        code{code},
        data1{data1},
        data2{data2}
    { }
};

}

#endif // SDLEVENT_HPP_INCLUDED
