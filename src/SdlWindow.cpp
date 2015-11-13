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
        item.w->Paint(screen, false);

    screen.Flip();
}

void Window::ShowDialog()
{
    Redraw();

    SDL_Event ev;
    bool quit = false;

    Widget * focused = nullptr;
    bool pressed = false;

    while(!quit)
    {
        SDL_WaitEvent(&ev);

        switch(ev.type)
        {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
            {
                MouseClickEvent e(ev.button.button, ev.button.state, ev.button.x, ev.button.y);
                pressed = false;

                for(auto item : Items)
                {
                    item.w->MouseClick(screen, e);
                    if (e.IsDone())
                    {
                        focused = item.w;
                        pressed = true;
                        break;
                    }
                }
                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                MouseClickEvent e(ev.button.button, ev.button.state, ev.button.x, ev.button.y);
                if(pressed)
                {
                    focused->MouseClick(screen, e);
                    pressed = false;
                }
                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMoveEvent e(ev.motion.state, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);
                if(pressed)
                    focused->MouseMove(screen, e);
                break;
            }

            case SDL_KEYDOWN:
            {
                KeyboardEvent e(ev.key.keysym.mod, ev.key.keysym.sym, ev.key.keysym.unicode);
                if(focused)
                    focused->KeyPress(screen, e);
                break;
            }

            default:
                break;

        }

        screen.Flip();
    }
}

}
