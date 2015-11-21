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

    roundedRectangleColor(screen, location.x-1, location.y-1, location.x+_size.w, location.y+_size.h, 2, keret);
    boxColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, alapszin);

    if(down)
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*_size.h/stripes, location.x+_size.w-1, location.y+(y+1)*_size.h/stripes-1, 255, 255, 255, (y)*3);
    else
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*_size.h/stripes, location.x+_size.w-1, location.y+(y+1)*_size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    rectangleColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, keretvilagos);


    Renderer textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

    Rect sp;
    sp.x = location.x + (_size.w - textsurf.width ()) / 2;
    sp.y = location.y + (_size.h - textsurf.height()) / 2;

    screen.Blit(textsurf, sp);
}

}
