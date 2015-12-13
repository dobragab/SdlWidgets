#ifndef SDLWIDGET_HPP_INCLUDED
#define SDLWIDGET_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlRenderer.hpp"
#include "SdlFont.hpp"
#include "SdlEvent.hpp"
#include "SdlTheme.hpp"
#include "Property.hpp"

namespace Sdl
{

class Window;

class Widget
{
protected:

    static Point defloc;

    Point location;
    Dimension size;
    bool isfocused;
    Window * parent = nullptr;

    GETTERSETTER(size, Dimension, Size)
    GETTERSETTER(location, Point, Location)
    GETTERSETTER(MainTheme.MainColor, Color, MainColor)

public:
    static Theme DefaultTheme;

    bool Enabled = true;
    bool Visible = true;

    Theme MainTheme;

    PROPERTY(Widget, Dimension, Size);
    PROPERTY(Widget, Point, Location);

    Widget(Point p, Dimension s, Theme theme = Widget::DefaultTheme) :
        location{p},
        size{s},
        MainTheme{theme}
    { }

    virtual void SetParent(Window * parent)
    {
        this->parent = parent;
    }

    virtual void SetFocus()
    {
        isfocused = true;
    }

    virtual void ReleaseFocus()
    {
        isfocused = false;
    }

    virtual bool IsClicked(Point p);

    virtual void MouseClick(MouseClickEvent& ev) = 0;
    virtual void MouseMove(MouseMoveEvent& ev) = 0;
    virtual void KeyPress(KeyboardEvent& ev) = 0;
    virtual void TextInput(TextInputEvent& ev) = 0;
    virtual void TimerTick(TimerEvent& ev) = 0;

    virtual void Paint(Renderer& screen);

    virtual ~Widget() {}
};

}

#endif // SDLWIDGET_HPP_INCLUDED
