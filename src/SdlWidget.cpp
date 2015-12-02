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

    Color ckeret{keret};
    roundedRectangleRGBA((SDL_Renderer*)screen, location.x-1, location.y-1, location.x+size.w, location.y+size.h, 2, ckeret.r, ckeret.g, ckeret.b, ckeret.a);

    Color calapszin{alapszin};
    boxRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, calapszin.r, calapszin.g, calapszin.b, calapszin.a);

    for (int y=0; y<stripes; ++y)
        boxRGBA((SDL_Renderer*)screen, location.x, location.y+y*size.h/stripes, location.x+size.w-1, location.y+(y+1)*size.h/stripes-1, 255, 255, 255, (stripes-1-y)*3);

    Color ckeretv{keretvilagos};
    rectangleRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w, location.y+size.h, ckeretv.r, ckeretv.g, ckeretv.b, ckeretv.a);
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
Color Slider::default_color = Color(0x00DDFF50);
Color ColorBox::default_color = Color(0x000000FF);

}
