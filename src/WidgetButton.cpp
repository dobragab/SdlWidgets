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

    int stripes = 20;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, MainTheme.InnerBorderColor);
    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.BaseColor);

    for (int y=0; y<stripes-1; ++y)
    {
        Color c(255, 255, 255, down ? y*3 : (stripes-1-y)*3);
        temp.draw_box(1, 1+y*size.h/stripes, size.w-2, (y+1)*size.h/stripes, c);
    }

    temp.draw_rectangle(1, 1, size.w-2, size.h-2, MainTheme.OuterBorderColor);

    Surface textsurf = WindowFont.Render(text, MainTheme.FontSize, MainTheme.MainColor, Font::Blended);

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
