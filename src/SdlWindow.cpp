#include "Sdl.hpp"
#include "SdlSurface.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"
#include "SdlTimer.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Window::Window(Dimension dim, const char * caption) :
    window{SDL_CreateWindow(caption,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            dim.w,
                            dim.h,
                            SDL_WINDOW_OPENGL)},
    screen{SDL_CreateRenderer(window, -1, 0)}
{
    if (window == nullptr)
        throw Sdl::exception();
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}


void Window::Redraw()
{
    Paint(screen);
    screen.Flip();
}

void Window::ShowDialog()
{
    Redraw();

    SDL_Event ev;

    bool to_redraw = false;

    while(!quit)
    {
        SDL_WaitEvent(&ev);
        to_redraw = false;

        switch(ev.type)
        {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                MouseClickEvent e(ev.button.button, ev.button.state, ev.button.x, ev.button.y);
                MouseClick(e);
                to_redraw = e.NeedsRedraw();
                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMoveEvent e(ev.motion.state, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);
                MouseMove(e);
                to_redraw = e.NeedsRedraw();
                break;
            }

            case SDL_KEYDOWN:
            {
                KeyboardEvent e{ev.key.keysym.scancode, Keycode(ev.key.keysym.sym), Keymod(ev.key.keysym.mod)};
                KeyPress(e);
                to_redraw = e.NeedsRedraw();
                break;
            }

            case SDL_TEXTINPUT:
            {
                TextInputEvent e(ev.text.text);
                TextInput(e);
                to_redraw = e.NeedsRedraw();
                break;
            }

            case SDL_TICK:
            {
                TimerEvent e(ev.user.code);
                TimerHandler * handler = static_cast<TimerHandler*>(ev.user.data1);
                handler->TimerTick(e);
                to_redraw = e.NeedsRedraw();
                break;
            }
            default:
                to_redraw = false;
                break;
        }

        if (to_redraw)
            Redraw();
    }
}

void Window::Close()
{
    quit = true;
}

}
