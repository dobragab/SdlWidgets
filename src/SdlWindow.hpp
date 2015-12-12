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
    Window(int16_t width, int16_t height, const char * caption = "");

    ~Window();

    void Add(Widget * w)
    {
        Items.push_back(Item{w, true});
    }

    void Add(Widget& w)
    {
        Items.push_back(Item{&w, false});
        w.SetParent(this);
    }

    void SetFocus(Widget * w) {
        if(focused != w)
        {
            if(focused)
                focused->ReleaseFocus();

            focused = w;
            focused->SetFocus();
        }
    }

    void ReleaseFocus(Widget * w) {
        if(focused)
        {
            focused->ReleaseFocus();
            focused = nullptr;
        }
    }

    void Redraw();
    void ShowDialog();

};

}

#endif // SDLWINDOW_H_INCLUDED
