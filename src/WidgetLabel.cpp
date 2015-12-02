#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Label::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Texture textsurf = WindowFont.Render(screen, text, default_font_size, (Color)gombfeliratszin, Font::Blended);

    Dimension textsize = textsurf.size();
    Rect sp{location.x, location.y, textsize.w, textsize.h};

    screen.Blit(textsurf, sp, true);
}

}
