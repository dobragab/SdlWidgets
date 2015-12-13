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
    int FontSize;
    Theme(
        Color InnerBorderColor,
        Color OuterBorderColor,
        Color BaseColor,
        Color MainColor,
        Font * MainFont,
        int FontSize
    ) :
        InnerBorderColor{InnerBorderColor},
        OuterBorderColor{OuterBorderColor},
        BaseColor{BaseColor},
        MainColor{MainColor},
        MainFont{MainFont},
        FontSize{FontSize}
    { }
};

extern Theme WidgetTheme;
extern Theme SliderTheme;
extern Theme ColorBoxTheme;

}

#endif // SDLTHEME_HPP_INCLUDED
