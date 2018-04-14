#ifndef SDLTHEME_HPP_INCLUDED
#define SDLTHEME_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlFont.hpp"

namespace Sdl
{

struct Theme
{
    Color InnerBorderColor;
    Color OuterBorderColor;
    Color BackgroundColor1;
    Color BackgroundColor2;
    Color BaseColor;
    Color MainColor;
    Font * MainFont;
    size_t FontSize;
    Font::RenderStyle FontStyle;
    Theme ( Color InnerBorderColor,
            Color OuterBorderColor,
            Color BackgroundColor1,
            Color BackgroundColor2,
            Color BaseColor,
            Color MainColor,
            Font * MainFont,
            size_t FontSize,
            Font::RenderStyle FontStyle) :

        InnerBorderColor{InnerBorderColor},
        OuterBorderColor{OuterBorderColor},
        BackgroundColor1{BackgroundColor1},
        BackgroundColor2{BackgroundColor2},
        BaseColor{BaseColor},
        MainColor{MainColor},
        MainFont{MainFont},
        FontSize{FontSize},
        FontStyle{FontStyle}
    { }
};

}

#endif // SDLTHEME_HPP_INCLUDED
