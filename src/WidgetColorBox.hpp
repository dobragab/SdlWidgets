#ifndef WIDGETCOLORBOX_HPP_INCLUDED
#define WIDGETCOLORBOX_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class ColorBox : public Widget
{
    static Color default_color;
    static Size defsize;

    Color color;

    GETTERSETTER(color, Color, DisplayedColor)

public:

    PROPERTY(ColorBox, Color, DisplayedColor);

    ColorBox(Color c = default_color) :
        Widget{defloc, defsize},
        color{c}
    { }

    virtual void Paint(Surface& screen) override;

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev) override { }
    virtual void MouseMove (Surface& sender, MouseMoveEvent & ev) override { }
    virtual void KeyPress  (Surface& sender, KeyboardEvent  & ev) override { }
    virtual void TimerTick (Surface& sender, TimerEvent     & ev) override { }

};

}

#endif // WIDGETCOLORBOX_HPP_INCLUDED
