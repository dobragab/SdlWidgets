#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Slider::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    draw_outer_border(temp);
    draw_base(temp);
    draw_stripes(temp);
    draw_inner_border(temp);

    temp.draw_box(1, 1, ((size.w-2)*(value - minvalue - 1)/(maxvalue - minvalue) + 1), size.h-2, MainTheme.MainColor);

    Texture cache{screen, temp};
    Rect dstrect(location.x, location.y, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

void Slider::MouseClick(MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.NeedsRedraw())
        return;

    if (ev.down)
    {
        if(IsClicked(ev.p))
        {
            parent->SetFocus(this);
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
    if (x <= location.x+1)
        Value = minvalue;
    else if (x > location.x + size.w - 2)
        Value = maxvalue;
    else
        Value = minvalue + (maxvalue - minvalue) * (x-location.x)/(size.w-2);
}

}
