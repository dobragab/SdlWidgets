#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

void ColorBox::Paint(Renderer& screen)
{
    if (!Visible)
        return;

    Color ckeret{keret};
    roundedRectangleRGBA((SDL_Renderer*)screen, location.x-1, location.y-1, location.x+size.w, location.y+size.h, 2, ckeret.r, ckeret.g, ckeret.b, ckeret.a);

    Color calapszin{alapszin};
    boxRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, calapszin.r, calapszin.g, calapszin.b, calapszin.a);

    Color ckeretv{keretvilagos};
    rectangleRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w, location.y+size.h, ckeretv.r, ckeretv.g, ckeretv.b, ckeretv.a);

    boxRGBA((SDL_Renderer*)screen, location.x, location.y, location.x+size.w-1, location.y+size.h-1, color.r, color.g, color.b, color.a);

}

}
