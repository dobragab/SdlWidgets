#ifndef WIDGETBUTTON_HPP_INCLUDED
#define WIDGETBUTTON_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class Button : public Widget
{
    std::u16string text;

    static Size defsize;

    bool down = false;

    Timer timer;

    GETTERSETTER(text, std::u16string, Text)

public:

    PROPERTY(Button, std::u16string, Text);

    Button(std::u16string text = u"Button") :
        Widget{defloc, defsize},
        text{text},
        timer{500, this}
    {
        timer.Start();
    }

    virtual void Paint(Renderer& screen) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TimerTick (TimerEvent     & ev) override;

    MouseClickedHandler MouseClicked = nullptr;
};

}

#endif // WIDGETBUTTON_HPP_INCLUDED
