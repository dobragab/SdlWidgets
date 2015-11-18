#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_gfxPrimitives.h>
#include "SDL_custom.hpp"

namespace Sdl
{

Window::Window(int16_t width, int16_t height, const char * caption) :
    screen{SDL_SetVideoMode(width, height, 0, SDL_HWSURFACE|SDL_DOUBLEBUF)}
{
    if(caption)
        SDL_WM_SetCaption(caption, caption);
}

Window::~Window()
{
    for(unsigned i = 0; i < Items.size(); ++i)
        if(Items[i].owner)
            delete Items[i].w;
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
                KeyboardEvent e(ev.key.keysym.mod, ev.key.keysym.sym, ev.key.keysym.unicode);
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

<<<<<<< HEAD
                to_redraw = e.IsDone();
=======
>>>>>>> 39486f12a9bfb6959780a21d7d3ff0e5dfe64a17
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
