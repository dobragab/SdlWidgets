#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void ColorBox::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    draw_outer_border(temp);
    draw_base(temp);
    draw_inner_border(temp);

    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.MainColor);

    Texture cache{screen, temp};
    Rect dstrect(location.x, location.y, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

}
