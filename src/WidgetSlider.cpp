#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Slider::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Widget::Paint(screen);

    boxColor(screen, location.x, location.y, location.x+((_size.w-1)*(value - minvalue)/(maxvalue - minvalue)), location.y+_size.h-1, (uint32_t)color);
}

void Slider::MouseClick(Renderer& sender, MouseClickEvent& ev)
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

void Slider::MouseMove (Renderer& sender, MouseMoveEvent & ev)
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
