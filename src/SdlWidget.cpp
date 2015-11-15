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

void SetFont(Font&& f)
{
    WindowFont = std::move(f);
}

void Widget::Paint(Surface& screen)
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

void Label::Paint(Surface& screen)
{
    Surface textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

    Rect sp;
    sp.x = location.x;
    sp.y = location.y;

    screen.Blit(textsurf, sp);
}

Size Button::defsize = Size(75, 23);
Size Label::defsize = Size(0, 0);
Size Slider::defsize = Size(100, 23);
Point Widget::defloc = Point(0, 0);
Color Widget::default_main_color = Color(0x00C0F0FF);
Color Slider::default_color = Color(0x00DDFF50);

void Button::MouseClick(Surface& sender, MouseClickEvent& ev)
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

void Button::Paint(Surface& screen)
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


    Surface textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

    Rect sp;
    sp.x = location.x + (_size.w - textsurf.width ()) / 2;
    sp.y = location.y + (_size.h - textsurf.height()) / 2;

    screen.Blit(textsurf, sp);
}

void Slider::Paint(Surface& screen)
{
    if (!Visible)
        return;

    Widget::Paint(screen);

    boxColor(screen, location.x, location.y, location.x+((_size.w-1)*(value - minvalue)/(maxvalue - minvalue)), location.y+_size.h-1, (uint32_t)color);
}

void Slider::MouseClick(Surface& sender, MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.IsDone())
        return;

    if (ev.down)
    {
        if(IsClicked(ev.p))
        {
            down = true;
            setval(ev.p.x);
            ev.Done();
        }
    }
    else
    {
        if(down)
            ev.Done();
        down = false;
    }
}

void Slider::MouseMove (Surface& sender, MouseMoveEvent & ev)
{
    if (!down || ev.IsDone())
        return;

    setval(ev.p.x);
    ev.Done();
}

void Slider::setval(int16_t x)
{
    if (x <= location.x)
        Value = minvalue;
    else if (x > location.x + _size.w)
        Value = maxvalue;
    else
        Value = minvalue + (maxvalue - minvalue) * (x-location.x-1)/(_size.w);
}


}
