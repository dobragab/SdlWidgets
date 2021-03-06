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
    static Dimension defsize;

    int minvalue = 0, maxvalue = 100;
    int value = 0;

    bool down = false;

    GETTERSETTER(MainTheme.MainColor, Color, BoxnColor)

    GETTER(minvalue, int, Minimum)
    GETTER(maxvalue, int, Maximum)
    GETTER(value, int, Value)

    void setMaximum(int const& val)
    {
        maxvalue = val;
        if (value < val)
            Value = val;
    }
    void setMinimum(int const& val)
    {
        minvalue = val;
        if (value > val)
            Value = val;
    }
    void setValue(int const& val)
    {
        if (val == value || val > maxvalue || val < minvalue)
            return;

        int oldval = value;
        value = val;
        if (valueChanged)
        {
            ValueChangedEvent<int> ev{oldval};
            valueChanged(*this, ev);
        }
    }

    void setval(int16_t x);

    typename ValueChangedEvent<int>::Handler valueChanged = nullptr;

public:
    static Theme DefaultTheme;

    Slider() :
        Widget{defloc, defsize, Slider::DefaultTheme}
    { }

    PROPERTY(Slider, int, Minimum);
    PROPERTY(Slider, int, Maximum);
    PROPERTY(Slider, int, Value);

    void ValueChanged(ValueChangedEvent<int>::Handler clicked)
    {
        valueChanged = std::move(clicked);
    }

    void ValueChanged(void(WidgetPanel::*clicked)(Widget&, ValueChangedEvent<int>&));

    template<typename Derived>
    void ValueChanged(void(Derived::*clicked)(Widget&, ValueChangedEvent<int>&))
    {
        ValueChanged(static_cast<void(WidgetPanel::*)(Widget&, ValueChangedEvent<int>&)>(clicked));
    }


    virtual void Paint(Renderer& screen, Point offset) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override;
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TextInput (TextInputEvent & ev) override { }

};

}

#endif // WIDGETSLIDER_HPP_INCLUDED
