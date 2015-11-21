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

    roundedRectangleColor(screen, location.x-1, location.y-1, location.x+_size.w, location.y+_size.h, 2, keret);
    boxColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, alapszin);

    for (int y=0; y<stripes; ++y)
        boxRGBA(screen, location.x, location.y+y*_size.h/stripes, location.x+_size.w-1, location.y+(y+1)*_size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    rectangleColor(screen, location.x, location.y, location.x+_size.w-1, location.y+_size.h-1, keretvilagos);
}

bool Widget::IsClicked(Point p)
{
    return  p.x >= location.x &&
            p.x <= location.x + _size.w &&
            p.y >= location.y &&
            p.y <= location.y + _size.h;
}

Size Button::defsize = Size(75, 23);
Size Label::defsize = Size(0, 0);
Size Slider::defsize = Size(100, 23);
Size ColorBox::defsize = Size(128, 32);
Point Widget::defloc = Point(0, 0);
Color Widget::default_main_color = Color(0x00C0F0FF);
Color Slider::default_color = Color(0x00DDFF50);
Color ColorBox::default_color = Color(0x000000FF);

}
