#ifndef SDLWIDGET_HPP_INCLUDED
#define SDLWIDGET_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlSurface.hpp"
#include "SdlFont.hpp"
#include "SdlEvent.hpp"
#include "Property.hpp"

namespace Sdl
{

uint32_t const hatter = 0x303030FF;
uint32_t const keret = 0x000000FF;
uint32_t const alapszin = 0x101010FF;
uint32_t const keretvilagos = 0xFFFFFF20;
uint32_t const gombfeliratszin = 0x00C0F0FF;
uint32_t const csuszkaszin = 0x00FFFF50;
uint32_t const feliratszin = 0x00C0F0FF;

extern Font WindowFont;
void SetFont(Font&& f);

class Widget;
typedef void (*MouseClickedHandler)(Widget& sender, MouseClickEvent& ev);
typedef void (*MouseMovedHandler)(Widget& sender, MouseMoveEvent& ev);
typedef void (*KeyPressHandler)(Widget& sender, KeyboardEvent& ev);
typedef void (*ValueChangedHandler)(Widget& sender);

class Widget
{
protected:

    static Color default_main_color;
    static Point defloc;

    Point location;
    Size _size;
    Color maincolor = default_main_color;

    GETTERSETTER(_size, Size, size)
    GETTERSETTER(location, Point, Location)
    GETTERSETTER(maincolor, Color, MainColor)

public:

    bool Enabled = true;
    bool Visible = true;

    PROPERTY(Widget, Size, size);
    PROPERTY(Widget, Point, Location);

    Widget(Point p, Size s) :
        location{p},
        _size{s}
    { }

    virtual bool IsClicked(Point p);

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev) = 0;
    virtual void MouseMove(Surface& sender, MouseMoveEvent& ev) = 0;
    virtual void KeyPress(Surface& sender, KeyboardEvent& ev) = 0;
    virtual void TimerTick(Surface& sender, TimerEvent& ev) = 0;

    virtual void Paint(Surface& screen);

    virtual ~Widget() {}
};

}

#endif // SDLWIDGET_HPP_INCLUDED
