#ifndef WIDGETSLIDER_HPP_INCLUDED
#define WIDGETSLIDER_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class Slider : public Widget
{
    static Size defsize;
    static Color default_color;

    int minvalue = 0, maxvalue = 100;
    int value = 0;
    Color color = default_color;


    bool down = false;


    GETTERSETTER(minvalue, int, Minimum)
    GETTERSETTER(maxvalue, int, Maximum)
    GETTERSETTER(color, Color, BoxColor)

    GETTER(value, int, Value)
    void setValue(int const& val)
    {
        value = val;
        if (ValueChanged)
            ValueChanged(*this);
    }

    void setval(int16_t x);

public:

    Slider() :
        Widget{defloc, defsize}
    { }

    PROPERTY(Slider, int, Minimum);
    PROPERTY(Slider, int, Maximum);
    PROPERTY(Slider, int, Value);

    ValueChangedHandler ValueChanged = nullptr;

    virtual void Paint(Renderer& screen) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override;
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TimerTick (TimerEvent     & ev) override { }

};

}

#endif // WIDGETSLIDER_HPP_INCLUDED
