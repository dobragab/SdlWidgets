#ifndef SDLEVENT_HPP_INCLUDED
#define SDLEVENT_HPP_INCLUDED

#include "Sdl.hpp"
#include <functional>

namespace Sdl
{

class Event
{
    bool redraw = false;

public:
    inline void Redraw()
    {
        redraw = true;
    }
    inline bool NeedsRedraw()
    {
        return redraw;
    }
};

class Widget;

struct KeyboardEvent : public Event
{
    using Handler = std::function<void(Widget& sender, KeyboardEvent& ev)>;

    uint16_t modifiers; // SDLMod
    uint16_t keysym;    // SDLKey

    KeyboardEvent(uint16_t modifiers, uint16_t keysym) :
        modifiers{modifiers},
        keysym{keysym}
    { }
};

struct TextInputEvent : public Event
{
    using Handler = std::function<void(Widget& sender, TextInputEvent& ev)>;

    std::u16string text;

    TextInputEvent(std::u16string text) :
        text{text}
    { }
};

struct MouseClickEvent : public Event
{
    using Handler = std::function<void(Widget& sender, MouseClickEvent& ev)>;

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
    using Handler = std::function<void(Widget& sender, MouseMoveEvent& ev)>;

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
    using Handler = std::function<void(Widget& sender, TimerEvent& ev)>;

    int code;
    void * data1;
    void * data2;

    TimerEvent(int code, void * data1, void * data2) :
        code{code},
        data1{data1},
        data2{data2}
    { }
};

template<typename T>
struct ValueChangedEvent : public Event
{
    using Handler = std::function<void(Widget& sender, ValueChangedEvent& ev)>;

    T oldvalue;

    ValueChangedEvent(T oldvalue) :
        oldvalue{oldvalue}
    { }
};

using TextChangedEvent = ValueChangedEvent<std::u16string>;

}

#endif // SDLEVENT_HPP_INCLUDED
