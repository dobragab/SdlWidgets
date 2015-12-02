#ifndef SDLWIDGET_HPP_INCLUDED
#define SDLWIDGET_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlRenderer.hpp"
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

class Widget
{
protected:

    static Color default_main_color;
    static Point defloc;
    static int default_font_size;

    Point location;
    Dimension size;
    Color maincolor = default_main_color;

    GETTERSETTER(size, Dimension, Size)
    GETTERSETTER(location, Point, Location)
    GETTERSETTER(maincolor, Color, MainColor)

public:

    bool Enabled = true;
    bool Visible = true;

    PROPERTY(Widget, Dimension, Size);
    PROPERTY(Widget, Point, Location);

    Widget(Point p, Dimension s) :
        location{p},
        size{s}
    { }

    virtual bool IsClicked(Point p);

    virtual void MouseClick(MouseClickEvent& ev) = 0;
    virtual void MouseMove(MouseMoveEvent& ev) = 0;
    virtual void KeyPress(KeyboardEvent& ev) = 0;
    virtual void TimerTick(TimerEvent& ev) = 0;

    virtual void Paint(Renderer& screen);

    virtual ~Widget() {}
};

}

#endif // SDLWIDGET_HPP_INCLUDED
