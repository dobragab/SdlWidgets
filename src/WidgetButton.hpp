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
    std::wstring text;

    static Size defsize;

    bool down = false;

    GETTERSETTER(text, std::wstring, Text)

public:

    PROPERTY(Button, std::wstring, Text);

    Button(std::wstring text = L"Button") :
        Widget{defloc, defsize},
        text{text}
    { }

    virtual void Paint(Surface& screen) override;

    virtual void MouseClick(Surface& sender, MouseClickEvent& ev) override;
    virtual void MouseMove (Surface& sender, MouseMoveEvent & ev) override { }
    virtual void KeyPress  (Surface& sender, KeyboardEvent  & ev) override { }
    virtual void TimerTick (Surface& sender, TimerEvent     & ev) override { }

    MouseClickedHandler MouseClicked = nullptr;
};

}

#endif // WIDGETBUTTON_HPP_INCLUDED
