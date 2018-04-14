#ifndef WIDGETLABEL_HPP_INCLUDED
#define WIDGETLABEL_HPP_INCLUDED

#include <utility>

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class Label : public Widget
{
    static Dimension defsize;

    std::string text;
    GETTERSETTER(text, std::string, Text)

public:

    PROPERTY(Label, std::string, Text);

    Label(std::string text = "Label") :
        Widget{defloc, defsize},
        text{std::move(text)}
    { }

    virtual void Paint(Renderer& screen, Point offset) override;

    virtual void MouseClick(MouseClickEvent& ev) override { }
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TextInput (TextInputEvent & ev) override { }

};

}

#endif // WIDGETLABEL_HPP_INCLUDED
