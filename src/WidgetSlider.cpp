#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Slider::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Widget::Paint(screen);

    boxRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+((_size.w-1)*(value - minvalue)/(maxvalue - minvalue)), location.y+_size.h-1, color.r, color.g, color.b, color.a);
}

void Slider::MouseClick(MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.NeedsRedraw())
        return;

    if (ev.down)
    {
        if(IsClicked(ev.p))
        {
            down = true;
            setval(ev.p.x);
            ev.Redraw();
        }
    }
    else
    {
        if(down)
            ev.Redraw();
        down = false;
    }
}

void Slider::MouseMove (MouseMoveEvent & ev)
{
    if (!down || ev.NeedsRedraw())
        return;

    setval(ev.p.x);
    ev.Redraw();
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
