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

class WidgetContainer;

class Widget
{
protected:

    static Point defloc;

    Point location;
    Dimension size;
    bool isfocused;
    WidgetContainer * parent = nullptr;

    GETTERSETTER(size, Dimension, Size)
    GETTERSETTER(location, Point, Location)

    template<typename TARGET>
    void draw_outer_border(TARGET& target)
    {
        target.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, MainTheme.OuterBorderColor);
    }

    template<typename TARGET>
    void draw_inner_border(TARGET& target)
    {
        target.draw_rectangle(1, 1, size.w-2, size.h-2, MainTheme.InnerBorderColor);
    }

    template<typename TARGET>
    void draw_stripes(TARGET& target, bool pushed = false)
    {
        if(pushed)
            for (int y = 0; y < size.h - 2; ++y)
            {
                Color c = Color::Transition(MainTheme.BackgroundColor1, MainTheme.BackgroundColor2, double(y) / (size.h-3));
                target.draw_hline(1, size.w-2, y+1, c);
            }
        else
            for (int y = 0; y < size.h - 2; ++y)
            {
                Color c = Color::Transition(MainTheme.BackgroundColor2, MainTheme.BackgroundColor1, double(y) / (size.h-3));
                target.draw_hline(1, size.w-2, y+1, c);
            }
    }

    template<typename TARGET>
    void draw_base(TARGET& target)
    {
        target.draw_box(1, 1, size.w-2, size.h-2, MainTheme.BaseColor);
    }

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

    virtual void SetParent(WidgetContainer * parent)
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

    virtual void Paint(Renderer& screen) = 0;

    virtual ~Widget() {}
};

}

#endif // SDLWIDGET_HPP_INCLUDED
