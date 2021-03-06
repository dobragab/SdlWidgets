#ifndef WIDGETCONTAINER_HPP_INCLUDED
#define WIDGETCONTAINER_HPP_INCLUDED

#include "SdlWidget.hpp"

#include <vector>

namespace Sdl
{

class WidgetPanel : public Widget
{
    struct Item
    {
        Widget * w;
        bool owner;

        Item(Widget * w, bool owner) :
            w{w},
            owner{owner}
        { }
    };

    std::vector<Item> Items;

    Widget * focused = nullptr;

public:

    using Widget::Widget;
    ~WidgetPanel();

    static Color DefaultColor;

    Color BackgroundColor = DefaultColor;

    void Add(Widget * w);
    void Add(Widget& w);

    void Remove(Widget * w);
    void Remove(Widget& w);

    void SetFocus(Widget& w);
    void ReleaseFocus();

    void MouseClick(MouseClickEvent& ev) override;
    void MouseMove(MouseMoveEvent& ev) override;
    void KeyPress(KeyboardEvent& ev) override;
    void TextInput(TextInputEvent& ev) override;

    void Paint(Renderer& screen, Point offset) override;
};

}

#endif // WIDGETCONTAINER_HPP_INCLUDED
