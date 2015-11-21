#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Window::Window(int16_t width, int16_t height, const char * caption) :
    window{SDL_CreateWindow(caption,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width,
                            height,
                            SDL_WINDOW_OPENGL)},
    screen{SDL_CreateRenderer(window, -1, 0)}
{ }

Window::~Window()
{
    for(unsigned i = 0; i < Items.size(); ++i)
        if(Items[i].owner)
            delete Items[i].w;

    SDL_DestroyWindow(window);
}

void Window::Redraw()
{
    screen.Fill(hatter);

    for(auto item : Items)
        item.w->Paint(screen);

    screen.Flip();
}

void Window::ShowDialog()
{
    Redraw();

    SDL_Event ev;
    bool quit = false;

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
                for (int i = Items.size() - 1; i >= 0; --i)
                    Items[i].w->MouseClick(screen, e);

                to_redraw = e.IsDone();
                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMoveEvent e(ev.motion.state, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);
                for (int i = Items.size() - 1; i >= 0; --i)
                    Items[i].w->MouseMove(screen, e);

                to_redraw = e.IsDone();
                break;
            }

            case SDL_KEYDOWN:
            {
                KeyboardEvent e(ev.key.keysym.mod, ev.key.keysym.sym);
                for (int i = Items.size() - 1; i >= 0; --i)
                    Items[i].w->KeyPress(screen, e);

                to_redraw = e.IsDone();
                break;
            }

            case SDL_TICK:
            {
                TimerEvent e(ev.user.code, ev.user.data1, ev.user.data2);
                for (int i = Items.size() - 1; i >= 0; --i)
                    if (Items[i].w == ev.user.data1)
                        Items[i].w->TimerTick(screen, e);

                to_redraw = e.IsDone();
                break;
            }
            default:
                to_redraw = false;
                break;

        }

        if (to_redraw)
        {
            Redraw();
#ifdef DEBUG
            puts("Had to redraw...");
#endif
        }

        screen.Flip();
    }
}

}
