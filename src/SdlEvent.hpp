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

    Scancode scancode;
    Keycode keysym;
    Keymod modifiers;

    KeyboardEvent(Scancode scancode, Keycode keysym, Keymod modifiers) :
        scancode{scancode},
        keysym{keysym},
        modifiers{modifiers}
    { }
};

struct TextInputEvent : public Event
{
    using Handler = std::function<void(Widget& sender, TextInputEvent& ev)>;

    std::string text;

    TextInputEvent(std::string text) :
        text{text}
    { }
};

struct MouseClickEvent : public Event
{
    using Handler = std::function<void(Widget& sender, MouseClickEvent& ev)>;

    MouseButton button;
    bool down;
    uint8_t no_clicks;
    Point p;

    MouseClickEvent(MouseButton button, bool down, uint8_t no_clicks, Point p) :
        button{button},
        down{down},
        p{p}
    { }
};

struct MouseMoveEvent : public Event
{
    using Handler = std::function<void(Widget& sender, MouseMoveEvent& ev)>;

    MouseButtonState state;
    Point p;
    Point vec;

    MouseMoveEvent(MouseButtonState state, Point p, Point vec) :
        state{state},
        p{p},
        vec{vec}
    { }
};

struct TimerEvent : public Event
{
    using Handler = std::function<void(Widget& sender, TimerEvent& ev)>;

    uint32_t interval;

    explicit TimerEvent(uint32_t interval) :
        interval{interval}
    { }
};

template<typename T>
struct ValueChangedEvent : public Event
{
    using Handler = std::function<void(Widget& sender, ValueChangedEvent& ev)>;

    T oldvalue;

    explicit ValueChangedEvent(T oldvalue) :
        oldvalue{oldvalue}
    { }
};

using TextChangedEvent = ValueChangedEvent<std::string>;

}

#endif // SDLEVENT_HPP_INCLUDED
