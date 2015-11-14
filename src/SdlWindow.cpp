#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_gfxPrimitives.h>

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
        to_redraw = true;

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

                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMoveEvent e(ev.motion.state, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);
                for (int i = Items.size() - 1; i >= 0; --i)
                    Items[i].w->MouseMove(screen, e);

                break;
            }

            case SDL_KEYDOWN:
            {
                KeyboardEvent e(ev.key.keysym.mod, ev.key.keysym.sym, ev.key.keysym.unicode);
                for (int i = Items.size() - 1; i >= 0; --i)
                    Items[i].w->KeyPress(screen, e);

                break;
            }

            default:
                to_redraw = false;
                break;

        }

        if (to_redraw)
            Redraw();

        screen.Flip();
    }
}

}
