#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void ColorBox::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, MainTheme.InnerBorderColor);
    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.BaseColor);
    temp.draw_rectangle(1, 1, size.w-2, size.h-2, MainTheme.OuterBorderColor);
    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.MainColor);

    Texture cache{screen, temp};
    Rect dstrect(location.x, location.y, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

}
