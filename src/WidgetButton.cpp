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
            down = true;
            ev.Redraw();
        }
    }
    else
    {
        if (down && MouseClicked && IsClicked(ev.p))
            MouseClicked(*this, ev);

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

    Color ckeret{keret};
    roundedRectangleRGBA((SDL_Renderer*)screen, location.x-1, location.y-1, location.x+size.w, location.y+size.h, 2, ckeret.r, ckeret.g, ckeret.b, ckeret.a);

    Color calapszin{alapszin};
    boxRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, calapszin.r, calapszin.g, calapszin.b, calapszin.a);

    if(down)
        for (int y=0; y<stripes; ++y)
            boxRGBA((SDL_Renderer*)screen, location.x, location.y+y*size.h/stripes, location.x+size.w-1, location.y+(y+1)*size.h/stripes-1, 255, 255, 255, (y)*3);
    else
        for (int y=0; y<stripes; ++y)
            boxRGBA((SDL_Renderer*)screen, location.x, location.y+y*size.h/stripes, location.x+size.w-1, location.y+(y+1)*size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    Color ckeretv{keretvilagos};
    rectangleRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w, location.y+size.h, ckeretv.r, ckeretv.g, ckeretv.b, ckeretv.a);


    Texture textsurf = WindowFont.Render(screen, text, default_font_size, (Color)gombfeliratszin, Font::Blended);

    Dimension textsize = textsurf.size();
    Rect sp;

    sp.x = location.x + (size.w - textsize.w) / 2;
    sp.y = location.y + (size.h - textsize.h) / 2;
    sp.w = textsize.w;
    sp.h = textsize.h;

    screen.Blit(textsurf, sp, true);
}

void Button::TimerTick (TimerEvent& ev)
{
    Visible = !Visible;
    ev.Redraw();
}

}
