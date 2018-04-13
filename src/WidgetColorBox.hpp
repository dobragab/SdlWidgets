#ifndef WIDGETCOLORBOX_HPP_INCLUDED
#define WIDGETCOLORBOX_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlEvent.hpp"
#include "SdlWidget.hpp"
#include "Property.hpp"

namespace Sdl
{

class ColorBox : public Widget
{
    static Dimension defsize;

    GETTERSETTER(MainTheme.MainColor, Color, DisplayedColor)

public:
    static Theme DefaultTheme;

    PROPERTY(ColorBox, Color, DisplayedColor);

    ColorBox() :
        Widget{defloc, defsize, ColorBox::DefaultTheme}
    { }

    virtual void Paint(Renderer& screen) override;

    virtual void MouseClick(MouseClickEvent& ev) override { }
    virtual void MouseMove (MouseMoveEvent & ev) override { }
    virtual void KeyPress  (KeyboardEvent  & ev) override { }
    virtual void TextInput (TextInputEvent & ev) override { }

};

}

#endif // WIDGETCOLORBOX_HPP_INCLUDED
