#ifndef SDLWINDOW_H_INCLUDED
#define SDLWINDOW_H_INCLUDED

#include "Sdl.hpp"
#include "SdlWidget.hpp"

#include <vector>

namespace Sdl
{

class Window
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

    SDL_Window * window = nullptr;
    Renderer screen;

    std::vector<Item> Items;

    Widget * focused = nullptr;

public:
    static Color DefaultColor;

    Color BackgroundColor = DefaultColor;

    Window(int16_t width, int16_t height, const char * caption = "");

    ~Window();

    void Add(Widget * w);
    void Add(Widget& w);

    void SetFocus(Widget * w);
    void ReleaseFocus();

    void Redraw();
    void ShowDialog();
};

}

#endif // SDLWINDOW_H_INCLUDED
