#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Font WindowFont;

void SetFont(Font&& f)
{
    WindowFont = std::move(f);
}

void Widget::Paint(Renderer& screen)
{
    int stripes = 20;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, Color(keret));
    temp.draw_box(1, 1, size.w-2, size.h-2, Color(alapszin));

    for (int y=0; y<stripes; ++y)
    {
        Color c(255, 255, 255, (stripes-1-y)*3);
        temp.draw_box(1, 1+y*size.h/stripes, size.w-2, (y+1)*size.h/stripes, c);
    }

    temp.draw_rectangle(1, 1, size.w-2, size.h-2, Color(keretvilagos));

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

Dimension Button::defsize = Dimension(75, 23);
Dimension Label::defsize = Dimension(0, 0);
Dimension Slider::defsize = Dimension(100, 23);
Dimension ColorBox::defsize = Dimension(128, 32);
Point Widget::defloc = Point(0, 0);
Color Widget::default_main_color = Color(0x00C0F0FF);
Color Slider::default_color = Color(0x00CCFF75);
Color ColorBox::default_color = Color(0x000000FF);

int Widget::default_font_size = 16;

}
