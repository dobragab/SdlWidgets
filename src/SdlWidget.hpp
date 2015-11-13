#ifndef SDLWIDGET_HPP_INCLUDED
#define SDLWIDGET_HPP_INCLUDED

#include "Sdl.hpp"
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

class Widget
{
protected:
    Point location;
    Size _size;

    Size getsize() const
    {
        return _size;
    }
    void setsize(Size const& s)
    {
        _size = s;
        // TODO: UPDATE EVENT
    }

    Point getLocation() const
    {
        return location;
    }
    void setLocation(Point const& p)
    {
        location = p;
        // TODO: UPDATE EVENT
    }


public:

    PROPERTY(Widget, Size, size);
    PROPERTY(Widget, Point, Location);

    Widget(Point p, Size s) :
        location{p},
        _size{s},
        size{*this},
        Location{*this}
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
    std::wstring text;

    static Size defsize;
    static Point defloc;

    std::wstring getText() const
    {
        return text;
    }
    void setText(std::wstring const& t)
    {
        text = t;
        // TODO: UPDATE EVENT
    }

public:

    PROPERTY(Button, std::wstring, Text);

    Button(std::wstring text) :
        Widget{defloc, defsize},
        text{text},
        Text{*this}
    { }

    virtual void Paint(Surface& screen, bool down = false) override
    {
        Widget::Paint(screen, down);

        Surface textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

        Rect sp;
        sp.x = location.x + (_size.w - textsurf.width ()) / 2;
        sp.y = location.y + (_size.h - textsurf.height()) / 2;

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
