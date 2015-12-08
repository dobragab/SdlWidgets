#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void ColorBox::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, Color(keret));
    temp.draw_box(1, 1, size.w-2, size.h-2, Color(alapszin));
    temp.draw_rectangle(1, 1, size.w-2, size.h-2, Color(keretvilagos));
    temp.draw_box(1, 1, size.w-2, size.h-2, color);

    Texture cache{screen, temp};
    Rect dstrect(location.x, location.y, size.w, size.h);

    screen.Blit(cache, dstrect, true);
}

}
