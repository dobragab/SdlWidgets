#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include "SdlWindow.hpp"
#include "WidgetContainer.hpp"

namespace Sdl
{

class WidgetWindow : public Window, public WidgetContainer
{
public:
    WidgetWindow(Dimension dim, const char * caption = "")
        : Window(dim, caption)
        , WidgetContainer(Point(0, 0), dim)
    { }

private:
    void MouseClick(MouseClickEvent& ev) override
    {
        WidgetContainer::MouseClick(ev);
    }
    void MouseMove(MouseMoveEvent& ev) override
    {
        WidgetContainer::MouseMove(ev);
    }
    void KeyPress(KeyboardEvent& ev) override
    {
        WidgetContainer::KeyPress(ev);
    }
    void TextInput(TextInputEvent& ev) override
    {
        WidgetContainer::TextInput(ev);
    }

    void Paint(Renderer& screen) override
    {
        WidgetContainer::Paint(screen);
    }
};

}


#endif // WIDGETWINDOW_H
