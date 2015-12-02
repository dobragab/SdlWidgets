#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Button::MouseClick(Renderer& sender, MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.IsDone())
        return;

    if (ev.down)
    {
        if(IsClicked(ev.p))
        {
            down = true;
            ev.Done();
        }
    }
    else
    {
        if (down && MouseClicked && IsClicked(ev.p))
            MouseClicked(*this, ev);

        if(down)
            ev.Done();

        down = false;
    }

}

void Button::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    int stripes = 20;

    Color ckeret{keret};
    roundedRectangleRGBA(screen, location.x-1, location.y-1, location.x+_size.w, location.y+_size.h, 2, ckeret.r, ckeret.g, ckeret.b, ckeret.a);

    Color calapszin{alapszin};
    boxRGBA(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, calapszin.r, calapszin.g, calapszin.b, calapszin.a);

    if(down)
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*_size.h/stripes, location.x+_size.w-1, location.y+(y+1)*_size.h/stripes-1, 255, 255, 255, (y)*3);
    else
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*_size.h/stripes, location.x+_size.w-1, location.y+(y+1)*_size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    Color ckeretv{keretvilagos};
    rectangleRGBA(screen, location.x, location.y, location.x+_size.w, location.y+_size.h, ckeretv.r, ckeretv.g, ckeretv.b, ckeretv.a);


    Texture textsurf = WindowFont.Render(screen, text, gombfeliratszin, Font::Blended);

    Size textsize = textsurf.size();
    Rect sp;

    sp.x = location.x + (_size.w - textsize.w) / 2;
    sp.y = location.y + (_size.h - textsize.h) / 2;
    sp.w = textsize.w;
    sp.h = textsize.h;

    screen.Blit(textsurf, sp, true);
}

}
