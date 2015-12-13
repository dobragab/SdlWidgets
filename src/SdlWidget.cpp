#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Widget::Paint(Renderer& screen)
{
    int stripes = 20;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, MainTheme.InnerBorderColor);
    temp.draw_box(1, 1, size.w-2, size.h-2, MainTheme.BaseColor);

    for (int y=0; y<stripes; ++y)
    {
        Color c(255, 255, 255, (stripes-1-y)*3);
        temp.draw_box(1, 1+y*size.h/stripes, size.w-2, (y+1)*size.h/stripes, c);
    }

    temp.draw_rectangle(1, 1, size.w-2, size.h-2, MainTheme.OuterBorderColor);

    Texture cache{screen, temp};
    Rect dstrect(location.x, location.y, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

bool Widget::IsClicked(Point p)
{
    return  p.x >= location.x &&
            p.x <= location.x + size.w &&
            p.y >= location.y &&
            p.y <= location.y + size.h;
}

}
