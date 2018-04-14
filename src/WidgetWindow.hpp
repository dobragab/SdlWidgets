#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include "SdlWindow.hpp"
#include "WidgetPanel.hpp"

namespace Sdl
{

class WidgetWindow : public Window, public WidgetPanel
{
public:
    WidgetWindow(Dimension dim, const char * caption = "")
        : Window(dim, caption)
        , WidgetPanel(Point(0, 0), dim)
    { }

private:
    void MouseClick(MouseClickEvent& ev) override
    {
        WidgetPanel::MouseClick(ev);
    }
    void MouseMove(MouseMoveEvent& ev) override
    {
        WidgetPanel::MouseMove(ev);
    }
    void KeyPress(KeyboardEvent& ev) override
    {
        WidgetPanel::KeyPress(ev);
    }
    void TextInput(TextInputEvent& ev) override
    {
        WidgetPanel::TextInput(ev);
    }

    void Paint(Renderer& screen, Point offset) override
    {
        WidgetPanel::Paint(screen, offset);
    }

    void Paint(Renderer& screen) override
    {
        WidgetPanel::Paint(screen, location);
    }
};

}


#endif // WIDGETWINDOW_H
