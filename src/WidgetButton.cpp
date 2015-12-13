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

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, MainTheme.InnerBorderColor);
    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.BaseColor);

    if(down)
        for (int y = 0; y < size.h - 2; ++y)
        {
            Color c = Color::Transition(MainTheme.BackgroundColor1, MainTheme.BackgroundColor2, double(y) / (size.h-3));
            temp.draw_hline(1, size.w-2, y+1, c);
        }
    else
        for (int y = 0; y < size.h - 2; ++y)
        {
            Color c = Color::Transition(MainTheme.BackgroundColor2, MainTheme.BackgroundColor1, double(y) / (size.h-3));
            temp.draw_hline(1, size.w-2, y+1, c);
        }

    temp.draw_rectangle(1, 1, size.w-2, size.h-2, MainTheme.OuterBorderColor);

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
