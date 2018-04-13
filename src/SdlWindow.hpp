#ifndef SDLWINDOW_H_INCLUDED
#define SDLWINDOW_H_INCLUDED

#include "Sdl.hpp"
#include "SdlWidget.hpp"

#include <vector>

namespace Sdl
{

class Window
{
    bool quit = false;

    SDL_Window * window = nullptr;
    Renderer screen;

    virtual void MouseClick(MouseClickEvent& ev) = 0;
    virtual void MouseMove(MouseMoveEvent& ev) = 0;
    virtual void KeyPress(KeyboardEvent& ev) = 0;
    virtual void TextInput(TextInputEvent& ev) = 0;

    virtual void Paint(Renderer& screen) = 0;

public:

    Window(Dimension dim, const char * caption = "");

    virtual ~Window();

    void Redraw();
    void ShowDialog();

    void Close();
};

}

#endif // SDLWINDOW_H_INCLUDED
