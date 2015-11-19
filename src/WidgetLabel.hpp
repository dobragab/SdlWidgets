#ifndef WIDGETLABEL_HPP_INCLUDED
#define WIDGETLABEL_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class Label : public Widget
{
    static Size defsize;

    std::wstring text;
    GETTERSETTER(text, std::wstring, Text)

public:

    PROPERTY(Label, std::wstring, Text);

    Label(std::wstring text = L"Button") :
        Widget{defloc, defsize},
        text{text}
    { }

    virtual void Paint(Surface& screen) override;

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev) override { }
    virtual void MouseMove (Surface& sender, MouseMoveEvent & ev) override { }
    virtual void KeyPress  (Surface& sender, KeyboardEvent  & ev) override { }
    virtual void TimerTick (Surface& sender, TimerEvent     & ev) override { }

};

}

#endif // WIDGETLABEL_HPP_INCLUDED
