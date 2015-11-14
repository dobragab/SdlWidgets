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
void SetFont(Font&& f);

class Widget;
typedef void (*MouseClickedHandler)(Widget& sender, MouseClickEvent& ev);
typedef void (*MouseMovedHandler)(Widget& sender, MouseMoveEvent& ev);
typedef void (*KeyPressHandler)(Widget& sender, KeyboardEvent& ev);

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
    }

    Point getLocation() const
    {
        return location;
    }
    void setLocation(Point const& p)
    {
        location = p;
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

    virtual void Paint(Surface& screen);

    virtual ~Widget() {}
};

class Button : public Widget
{
    std::wstring text;

    static Size defsize;
    static Point defloc;
    static Color default_color;

    bool down = false;

    std::wstring getText() const
    {
        return text;
    }
    void setText(std::wstring const& t)
    {
        text = t;
    }

public:

    PROPERTY(Button, std::wstring, Text);
    bool Enabled = true;
    bool Visible = true;

    Button(std::wstring text = L"Button") :
        Widget{defloc, defsize},
        text{text},
        Text{*this}
    { }

    virtual void Paint(Surface& screen) override;

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev);
    virtual void MouseMove (Surface& sender, MouseMoveEvent & ev) { }
    virtual void KeyPress  (Surface& sender, KeyboardEvent  & ev) { }

    MouseClickedHandler MouseClicked = nullptr;


};

}

#endif // SDLWIDGET_HPP_INCLUDED
