#include <iostream>

#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void TextBox::SetFocus()
{
    Widget::SetFocus();
    timer.Start();
}

void TextBox::ReleaseFocus()
{
    Widget::ReleaseFocus();
    cursor_visible = false;
    timer.Finish();
}

void TextBox::setText(std::u16string const& value)
{
    set_text(value);
    cursor_position = text.length();
}

void TextBox::set_text(std::u16string const& value)
{
    TextChangedEvent ev{text};
    text = value;
    if (TextChanged)
        TextChanged(*this, ev);
}

void TextBox::MouseClick(MouseClickEvent& ev)
{
    if (!Visible || ev.button != SDL_BUTTON_LEFT || ev.NeedsRedraw())
        return;


    if(IsClicked(ev.p))
    {
        parent->SetFocus(this);
        size_t min = 0, max = text.length();
        bool found = false;

        size_t current;
        while(!found && min <= max)
        {
            current = (min + max) / 2;
            std::u16string tempstring{text.begin(), text.begin() + current};
            int16_t cursor_x = WindowFont.RenderSize(tempstring, default_font_size).x;

            if(cursor_x <= ev.p.x - location.x)
            {
                if(current == max)
                    found = true;
                else
                {
                    tempstring = std::u16string{text.begin(), text.begin() + current + 1};
                    cursor_x = WindowFont.RenderSize(tempstring, default_font_size).x;

                    if(cursor_x > ev.p.x - location.x)
                        found = true;
                    else
                        min = current + 1;
                }
            }
            else
                max = current - 1;
        }

        if (cursor_position != current)
        {
            cursor_visible = true;
            timer.Finish();
            timer.Start();
            cursor_position = current;
        }
        ev.Redraw();
    }

}

void TextBox::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Surface temp{size.w, size.h};

    temp.draw_rounded_rectangle(0, 0, size.w-1, size.h-1, 2, Color(keret));
    temp.draw_box(1, 1, size.w-2, size.h-2, Color(alapszin));

    temp.draw_rectangle(1, 1, size.w-2, size.h-2, Color(keretvilagos));

    Surface textsurf = WindowFont.Render(text, default_font_size, (Color)gombfeliratszin, Font::Blended);

    Dimension textsize = textsurf.Size();
    Rect sp;

    sp.x = 0;
    sp.y = (size.h - textsize.h) / 2;
    sp.w = textsize.w;
    sp.h = textsize.h;

    temp.Blit(textsurf, sp);

    if(cursor_visible)
    {
        std::u16string tempstring{text, 0, cursor_position};
        int16_t cursor_x = WindowFont.RenderSize(tempstring, default_font_size).x;
        temp.draw_line((int16_t)cursor_x, (int16_t)0, (int16_t)cursor_x, (int16_t)size.h, (Color)gombfeliratszin);
    }

    Texture cache{screen, temp};
    Rect dstrect(location.x-1, location.y-1, size.w, size.h);

    screen.Blit(cache, nullptr, dstrect);
}

void TextBox::TimerTick (TimerEvent& ev)
{
    cursor_visible = !cursor_visible;
    ev.Redraw();
}

void TextBox::KeyPress (KeyboardEvent& ev) {

    uint16_t old_pos = cursor_position;

    switch(ev.keysym)
    {
    case (uint16_t)SDLK_RIGHT:
        if(cursor_position < text.length())
        {
            ++cursor_position;
            ev.Redraw();
        }
        break;
    case (uint16_t)SDLK_LEFT:
        if(0 < cursor_position)
        {
            --cursor_position;
            ev.Redraw();
        }
        break;
    case (uint16_t)SDLK_BACKSPACE:
        if(0 < cursor_position)
        {
            set_text(std::u16string{text.begin(), text.begin() + cursor_position - 1} +
                     std::u16string{text.begin() + cursor_position, text.end()});
            --cursor_position;
            ev.Redraw();
        }
        break;
    case (uint16_t)SDLK_DELETE:
        if(cursor_position < text.length())
        {
            set_text(std::u16string{text.begin(), text.begin() + cursor_position} +
                     std::u16string{text.begin() + cursor_position + 1, text.end()});
            ev.Redraw();
        }
        break;
    default:
        break;
    }

    if(cursor_position != old_pos)
    {
        cursor_visible = true;
        timer.Finish();
        timer.Start();
    }
}


void TextBox::TextInput (TextInputEvent& ev)
{
    set_text(std::u16string{text.begin(), text.begin() + cursor_position} +
             ev.text +
             std::u16string{text.begin() + cursor_position, text.end()});
    ++cursor_position;

    timer.Finish();
    timer.Start();
    cursor_visible = true;
    ev.Redraw();
}

}
