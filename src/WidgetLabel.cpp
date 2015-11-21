#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Label::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Texture textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

    Rect sp{location.x, location.y, textsurf->width(), textsurf->height()};

    screen.Blit(textsurf, sp, true);
}

}
