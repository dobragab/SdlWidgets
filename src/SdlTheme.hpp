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
    Color BaseColor;
    Color MainColor;
    Font * MainFont;
    size_t FontSize;
    Theme ( Color InnerBorderColor,
            Color OuterBorderColor,
            Color BaseColor,
            Color MainColor,
            Font * MainFont,
            size_t FontSize) :

        InnerBorderColor{InnerBorderColor},
        OuterBorderColor{OuterBorderColor},
        BaseColor{BaseColor},
        MainColor{MainColor},
        MainFont{MainFont},
        FontSize{FontSize}
    { }
};

}

#endif // SDLTHEME_HPP_INCLUDED
