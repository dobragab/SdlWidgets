#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void Label::Paint(Renderer& screen, Point offset)
{
    if (!Visible)
        return;

    Texture textsurf = MainTheme.MainFont->Render(screen, text, MainTheme.FontSize, MainTheme.MainColor, Font::Blended);

    Rect sp{location + offset, textsurf.Size()};

    screen.Blit(textsurf, nullptr, sp);
}

}
