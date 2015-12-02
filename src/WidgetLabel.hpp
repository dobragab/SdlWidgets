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

    std::u16string text;
    GETTERSETTER(text, std::u16string, Text)

public:

    PROPERTY(Label, std::u16string, Text);

    Label(std::u16string text = u"Label") :
        Widget{defloc, defsize},
        text{text}
    { }

    virtual void Paint(Renderer& screen) override;

    virtual void MouseClick(MouseClickEvent& ev) override { }
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TimerTick (TimerEvent     & ev) override { }

};

}

#endif // WIDGETLABEL_HPP_INCLUDED
