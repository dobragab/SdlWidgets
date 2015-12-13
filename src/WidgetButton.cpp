#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Button::MouseClick(MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.NeedsRedraw())
        return;

    if (ev.down)
    {
        if(IsClicked(ev.p))
        {
            parent->SetFocus(this);
            down = true;
            ev.Redraw();
        }
    }
    else
    {
        if (down && MouseClicked && IsClicked(ev.p))
        {
            parent->SetFocus(this);
            MouseClicked(*this, ev);
        }

        if(down)
            ev.Redraw();

        down = false;
    }
}

void Button::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    draw_outer_border(temp);
    draw_base(temp);
    draw_stripes(temp, down);
    draw_inner_border(temp);

    Surface textsurf = MainTheme.MainFont->Render(text, MainTheme.FontSize, MainTheme.MainColor, Font::Blended);

    Dimension textsize = textsurf.Size();
    Rect sp;

    sp.x = (size.w - textsize.w) / 2;
    sp.y = (size.h - textsize.h) / 2;
    sp.w = textsize.w;
    sp.h = textsize.h;

    temp.Blit(textsurf, sp);

    Texture cache{screen, temp};
    Rect dstrect(location.x-1, location.y-1, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

void Button::TimerTick (TimerEvent& ev)
{
    //Visible = !Visible;
    ev.Redraw();
}

}
