#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Label::Paint(Surface& screen)
{
    if (!Visible)
        return;

    Surface textsurf = WindowFont.Render(text, gombfeliratszin, Font::Blended);

    Rect sp{location.x, location.y};

    screen.Blit(textsurf, sp);
}

}
