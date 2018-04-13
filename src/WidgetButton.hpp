#ifndef WIDGETBUTTON_HPP_INCLUDED
#define WIDGETBUTTON_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class Button : public Widget, public TimerHandler
{
    std::string text;

    static Dimension defsize;

    bool down = false;

    Timer timer;

    GETTERSETTER(text, std::string, Text)

public:

    PROPERTY(Button, std::string, Text);

    Button(std::string text = "Button") :
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
    virtual void TextInput (TextInputEvent & ev) override { }
    virtual void TimerTick (TimerEvent     & ev) override;

    MouseClickEvent::Handler MouseClicked = nullptr;
};

}

#endif // WIDGETBUTTON_HPP_INCLUDED
