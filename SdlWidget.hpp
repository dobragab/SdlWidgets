#ifndef SDLWIDGET_HPP_INCLUDED
#define SDLWIDGET_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"

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

class Widget
{
protected:
    Point location;
    Size size;

public:

    Widget(Point p, Size s) :
        location{p},
        size{s}
    { }

    virtual bool IsClicked(Point p);

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev) = 0;
    virtual void MouseMove(Surface& sender, MouseMoveEvent& ev) = 0;
    virtual void KeyPress(Surface& sender, KeyboardEvent& ev) = 0;

    virtual void Paint(Surface& screen, bool down = false);

    virtual ~Widget() {}
};

class Button : public Widget
{
    std::wstring Text;

    static Size defsize;
    static Point defloc;

public:

    Button(std::wstring text) :
        Widget{defloc, defsize},
        Text{text}
    { }

    virtual void Paint(Surface& screen, bool down = false) override
    {
        Widget::Paint(screen, down);

        Surface textsurf = WindowFont.Render(Text, gombfeliratszin, Font::Blended);

        Rect sp;
        sp.x = defloc.x + (size.w - textsurf.width ()) / 2;
        sp.y = defloc.y + (size.h - textsurf.height()) / 2;

        screen.Blit(textsurf, sp);
    }

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev);

    virtual void MouseMove(Surface& sender, MouseMoveEvent& ev)
    { }

    virtual void KeyPress(Surface& sender, KeyboardEvent& ev)
    { }

};

}

#endif // SDLWIDGET_HPP_INCLUDED
