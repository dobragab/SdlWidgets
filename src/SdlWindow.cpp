#include "Sdl.hpp"
#include "SdlSurface.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"
#include "SdlTimer.hpp"

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
{
    if (window == nullptr)
        throw Sdl::exception();
}

Window::~Window()
{
    for(unsigned i = 0; i < Items.size(); ++i)
        if(Items[i].owner)
            delete Items[i].w;

    SDL_DestroyWindow(window);
}

void Window::Add(Widget * w)
{
    Items.push_back(Item{w, true});
    w->SetParent(this);
}

void Window::Add(Widget& w)
{
    Items.push_back(Item{&w, false});
    w.SetParent(this);
}

void Window::Remove(Widget * w)
{
    for(auto it = Items.begin(); it < Items.end(); ++it)
    {
        if(it->w == w)
        {
            if(it->owner)
                delete it->w;

            Items.erase(it);
            break;
        }

    }
}

void Window::Remove(Widget& w)
{
    Remove(&w);
}

void Window::SetFocus(Widget * w)
{
    if(focused != w)
    {
        if(focused)
            focused->ReleaseFocus();

        focused = w;
        focused->SetFocus();
    }
}

void Window::ReleaseFocus()
{
    if(focused)
    {
        focused->ReleaseFocus();
        focused = nullptr;
    }
}

void Window::Redraw()
{
    screen.Fill(BackgroundColor);

    for(auto item : Items)
        item.w->Paint(screen);

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
                for (int i = Items.size() - 1; i >= 0 && !e.NeedsRedraw(); --i)
                    Items[i].w->MouseClick(e);

                to_redraw = e.NeedsRedraw();

                if (!to_redraw)
                    ReleaseFocus();

                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMoveEvent e(ev.motion.state, ev.motion.x, ev.motion.y, ev.motion.xrel, ev.motion.yrel);
                for (int i = Items.size() - 1; i >= 0 && !e.NeedsRedraw(); --i)
                    Items[i].w->MouseMove(e);

                to_redraw = e.NeedsRedraw();
                break;
            }

            case SDL_KEYDOWN:
            {
                KeyboardEvent e{ev.key.keysym.scancode, Keycode(ev.key.keysym.sym), Keymod(ev.key.keysym.mod)};

                if(focused)
                {
                    focused->KeyPress(e);
                    to_redraw = e.NeedsRedraw();
                }
                break;
            }

            case SDL_TEXTINPUT:
            {
                TextInputEvent e(ev.text.text);

                if(focused)
                {
                    focused->TextInput(e);
                    to_redraw = e.NeedsRedraw();
                }
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
