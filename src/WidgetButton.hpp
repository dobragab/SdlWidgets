#ifndef WIDGETBUTTON_HPP_INCLUDED
#define WIDGETBUTTON_HPP_INCLUDED

#include <utility>

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

    MouseClickEvent::Handler mouseClicked;

public:

    PROPERTY(Button, std::string, Text);

    Button(std::string text = "Button") :
        Widget{defloc, defsize},
        text{std::move(text)},
        timer{500, this}
    {
        timer.Start();
    }

    virtual void Paint(Renderer& screen, Point offset) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TextInput (TextInputEvent & ev) override { }
    virtual void TimerTick (TimerEvent     & ev) override;

    void MouseClicked(MouseClickEvent::Handler clicked)
    {
        mouseClicked = std::move(clicked);
    }

    void MouseClicked(void(WidgetPanel::*clicked)(Widget&, MouseClickEvent&));

    template<typename Derived>
    void MouseClicked(void(Derived::*clicked)(Widget&, MouseClickEvent&))
    {
        MouseClicked(static_cast<void(WidgetPanel::*)(Widget&, MouseClickEvent&)>(clicked));
    }
};

}

#endif // WIDGETBUTTON_HPP_INCLUDED
