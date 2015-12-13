#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

bool Widget::IsClicked(Point p)
{
    return  p.x >= location.x &&
            p.x <= location.x + size.w &&
            p.y >= location.y &&
            p.y <= location.y + size.h;
}

}
