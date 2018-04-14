#include "WidgetPanel.hpp"

namespace Sdl
{

WidgetPanel::~WidgetPanel()
{
    for(unsigned i = 0; i < Items.size(); ++i)
        if(Items[i].owner)
            delete Items[i].w;
}

void WidgetPanel::Add(Widget * w)
{
    Items.push_back(Item{w, true});
    w->SetParent(this);
}

void WidgetPanel::Add(Widget& w)
{
    Items.push_back(Item{&w, false});
    w.SetParent(this);
}

void WidgetPanel::Remove(Widget * w)
{
    for(auto it = Items.begin(); it < Items.end(); ++it)
    {
        if(it->w == w)
        {
            if(it->owner)
                delete it->w;

            Items.erase(it);
            break;
        }

    }
}

void WidgetPanel::Remove(Widget& w)
{
    Remove(&w);
}

void WidgetPanel::SetFocus(Widget& w)
{
    if(focused != &w)
    {
        if(focused)
            focused->ReleaseFocus();

        focused = &w;
        focused->SetFocus();
    }
}

void WidgetPanel::ReleaseFocus()
{
    if(focused)
    {
        focused->ReleaseFocus();
        focused = nullptr;
    }
}

void WidgetPanel::MouseClick(MouseClickEvent& ev)
{
    MouseClickEvent ev_copy = ev;
    ev_copy.p = ev.p - location;
    for (int i = Items.size() - 1; i >= 0 && !ev_copy.NeedsRedraw(); --i)
        Items[i].w->MouseClick(ev_copy);
    if (!ev_copy.NeedsRedraw())
        ReleaseFocus();
    if (ev_copy.NeedsRedraw())
        ev.Redraw();
}

void WidgetPanel::MouseMove(MouseMoveEvent& ev)
{
    MouseMoveEvent ev_copy = ev;
    ev_copy.p = ev.p - location;
    for (int i = Items.size() - 1; i >= 0; --i)
        Items[i].w->MouseMove(ev_copy);
    if (ev_copy.NeedsRedraw())
        ev.Redraw();
}

void WidgetPanel::KeyPress(KeyboardEvent& ev)
{
    if (focused)
    {
        focused->KeyPress(ev);
    }
}

void WidgetPanel::TextInput(TextInputEvent& ev)
{
    if (focused)
    {
        focused->TextInput(ev);
    }
}

void WidgetPanel::Paint(Renderer& screen, Point offset)
{
    screen.Fill(Rect(location + offset, size), BackgroundColor);

    Point newoffset = location + offset;

    for(auto item : Items)
       item.w->Paint(screen, newoffset);
}

}
