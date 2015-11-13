#include "Sdl.hpp"
#include "SdlWidget.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_gfxPrimitives.h>

#include <string>

namespace Sdl
{

Font WindowFont;

void Widget::Paint(Surface& screen, bool down)
{
    int stripes = 20;

    roundedRectangleColor(screen, location.x-1, location.y-1, location.x+size.w, location.y+size.h, 2, keret);
    boxColor(screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, alapszin);

    if(down)
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*size.h/stripes, location.x+size.w-1, location.y+(y+1)*size.h/stripes-1, 255, 255, 255, (y)*3);
    else
        for (int y=0; y<stripes; ++y)
            boxRGBA(screen, location.x, location.y+y*size.h/stripes, location.x+size.w-1, location.y+(y+1)*size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    rectangleColor(screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, keretvilagos);
}

bool Widget::IsClicked(Point p)
{
    return  p.x >= location.x &&
            p.x <= location.x + size.w &&
            p.y >= location.y &&
            p.y <= location.y + size.h;
}

Size Button::defsize = Size(75, 40);
Point Button::defloc = Point(100, 100);

void Button::MouseClick(Surface& sender, MouseClickEvent& ev)
{
    if (!ev.down ||IsClicked(ev.p))
    {
        if(ev.button ==  SDL_BUTTON_LEFT)
            Paint(sender, ev.down);
        ev.Done();
    }

}


}
