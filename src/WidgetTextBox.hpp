#ifndef WIDGETTEXTBOX_HPP_INCLUDED
#define WIDGETTEXTBOX_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class TextBox : public Widget
{
    bool cursor_visible = false;

    uint16_t cursor_position = 0;

    std::u16string text;

    static Dimension defsize;

    Timer timer;

    GETTER(text, std::u16string, Text)
    void set_text(std::u16string const& value);

public:

    void setText(std::u16string const& value);

    PROPERTY(TextBox, std::u16string, Text);

    TextBox(std::u16string text = u"TextBox") :
        Widget{defloc, defsize},
        text{text},
        timer{500, this}
    {}

    virtual void SetFocus() override;
    virtual void ReleaseFocus() override;

    virtual void Paint(Renderer& screen) override;

    virtual void MouseClick(MouseClickEvent& ev) override;
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override;
    virtual void TextInput (TextInputEvent & ev) override;
    virtual void TimerTick (TimerEvent     & ev) override;

    TextChangedEvent::Handler TextChanged = nullptr;
};

}


#endif // WIDGETTEXTBOX_HPP_INCLUDED
