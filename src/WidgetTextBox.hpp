#ifndef WIDGETTEXTBOX_HPP_INCLUDED
#define WIDGETTEXTBOX_HPP_INCLUDED

#include <utility>

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class TextBox : public Widget, public TimerHandler
{
    bool cursor_visible = false;

    uint16_t cursor_position = 0;

    std::string text;

    static Dimension defsize;

    Timer timer;

    GETTER(text, std::string, Text)
    void set_text(std::string const& value);
    void setText(std::string const& value);

public:


    PROPERTY(TextBox, std::string, Text);

    TextBox(std::string text = "TextBox") :
        Widget{defloc, defsize},
        text{std::move(text)},
        timer{500, this}
    {}

    virtual void SetFocus() override;
    virtual void ReleaseFocus() override;

    virtual void Paint(Renderer& screen, Point offset) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override;
    virtual void TextInput (TextInputEvent & ev) override;
    virtual void TimerTick (TimerEvent     & ev) override;

    TextChangedEvent::Handler textChanged = nullptr;

    void TextChanged(TextChangedEvent::Handler clicked)
    {
        textChanged = std::move(clicked);
    }

    void TextChanged(void(WidgetPanel::*clicked)(Widget&, TextChangedEvent&));

    template<typename Derived>
    void TextChanged(void(Derived::*clicked)(Widget&, TextChangedEvent&))
    {
        TextChanged(static_cast<void(WidgetPanel::*)(Widget&, TextChangedEvent&)>(clicked));
    }
};

}


#endif // WIDGETTEXTBOX_HPP_INCLUDED
