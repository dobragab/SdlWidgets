#include "WidgetContainer.hpp"

namespace Sdl
{

WidgetContainer::~WidgetContainer()
{    for(unsigned i = 0; i < Items.size(); ++i)
        if(Items[i].owner)
            delete Items[i].w;
}

void WidgetContainer::Add(Widget * w)
{
    Items.push_back(Item{w, true});
    w->SetParent(this);
}

void WidgetContainer::Add(Widget& w)
{
    Items.push_back(Item{&w, false});
    w.SetParent(this);
}

void WidgetContainer::Remove(Widget * w)
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

void WidgetContainer::Remove(Widget& w)
{
    Remove(&w);
}

void WidgetContainer::SetFocus(Widget * w)
{
    if(focused != w)
    {
        if(focused)
            focused->ReleaseFocus();

        focused = w;
        focused->SetFocus();
    }
}

void WidgetContainer::ReleaseFocus()
{
    if(focused)
    {
        focused->ReleaseFocus();
        focused = nullptr;
    }
}

void WidgetContainer::MouseClick(MouseClickEvent& ev)
{
    for (int i = Items.size() - 1; i >= 0 && !ev.NeedsRedraw(); --i)
        Items[i].w->MouseClick(ev);
    if (!ev.NeedsRedraw())
        ReleaseFocus();
}

void WidgetContainer::MouseMove(MouseMoveEvent& ev)
{
    for (int i = Items.size() - 1; i >= 0 && !ev.NeedsRedraw(); --i)
        Items[i].w->MouseMove(ev);
}

void WidgetContainer::KeyPress(KeyboardEvent& ev)
{
    if (focused)
    {
        focused->KeyPress(ev);
    }
}

void WidgetContainer::TextInput(TextInputEvent& ev)
{
    if (focused)
    {
        focused->TextInput(ev);
    }
}

void WidgetContainer::Paint(Renderer& screen)
{
    screen.Fill(BackgroundColor);

    for(auto item : Items)
       item.w->Paint(screen);
}

}
