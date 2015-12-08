#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"
#include "SDL_gfx/SDL_gfxPrimitives.h"

namespace Sdl
{

Surface::Surface(SDL_Surface * surf) :
    surf{surf}
{
    if (!surf)
        throw Sdl::exception();
}

Surface::Surface(int width, int height) :
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
    surf{SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000)}
#else
    surf{SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF)}
#endif
{
    if (!surf)
        throw Sdl::exception();

    SDL_SetSurfaceAlphaMod(surf, 0xFF);
}

Surface::Surface(Surface&& old) :
    surf{old.surf}
{
    old.surf = nullptr;
}

Surface& Surface::operator=(Surface&& old)
{
    if (this != &old)
    {
        SDL_FreeSurface(surf);
        surf = old.surf;
        old.surf = nullptr;
    }
    return *this;
}

Surface::~Surface()
{
    SDL_FreeSurface(surf);
}

int Surface::Width() const
{
    return surf->w;
}

int Surface::Height() const
{
    return surf->h;
}

Surface::operator SDL_Surface*() const
{
    return surf;
}

// SDL_gfxPrimitives
bool Surface::draw_pixel(int16_t x, int16_t y, Color color)
{
    return !pixelColor(surf, x, y, (uint32_t) color);
}
bool Surface::draw_hline (int16_t x1, int16_t x2, int16_t y, Color color)
{
    return !hlineColor(surf, x1, x2, y, (uint32_t) color);
}
bool Surface::draw_vline (int16_t x, int16_t y1, int16_t y2, Color color)
{
    return !vlineColor(surf, x, y1, y2, (uint32_t) color);
}
bool Surface::draw_rectangle (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !rectangleColor(surf, x1, y1, x2, y2, (uint32_t) color);
}
bool Surface::draw_rounded_rectangle (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color)
{
    return !roundedRectangleColor(surf, x1, y1, x2, y2, rad, (uint32_t) color);
}
bool Surface::draw_box (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !boxColor(surf, x1, y1, x2, y2, (uint32_t) color);
}
bool Surface::draw_rounded_box (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color)
{
    return !roundedBoxColor(surf, x1, y1, x2, y2, rad, (uint32_t) color);
}
bool Surface::draw_line (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !lineColor(surf, x1, y1, x2, y2, (uint32_t) color);
}
bool Surface::draw_aaline (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !aalineColor(surf, x1, y1, x2, y2, (uint32_t) color);
}
bool Surface::draw_thick_line (int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width, Color color)
{
    return !thickLineColor(surf, x1, y1, x2, y2, width, (uint32_t) color);
}
bool Surface::draw_circle (int16_t x, int16_t y, int16_t rad, Color color)
{
    return !circleColor(surf, x, y, rad, (uint32_t) color);
}
bool Surface::draw_arc (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !arcColor(surf, x, y, rad, start, end, (uint32_t) color);
}
bool Surface::draw_aacircle (int16_t x, int16_t y, int16_t rad, Color color)
{
    return !aacircleColor(surf, x, y, rad, (uint32_t) color);
}
bool Surface::draw_filled_circle (int16_t x, int16_t y, int16_t r, Color color)
{
    return !filledCircleColor(surf, x, y, r, (uint32_t) color);
}
bool Surface::draw_ellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !ellipseColor(surf, x, y, rx, ry, (uint32_t) color);
}
bool Surface::draw_aaellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !aaellipseColor(surf, x, y, rx, ry, (uint32_t) color);
}
bool Surface::draw_filled_ellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !filledEllipseColor(surf, x, y, rx, ry, (uint32_t) color);
}
bool Surface::draw_pie (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !pieColor(surf, x, y, rad, start, end, (uint32_t) color);
}
bool Surface::draw_filled_pie (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !filledPieColor(surf, x, y, rad, start, end, (uint32_t) color);
}
bool Surface::draw_trigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !trigonColor(surf, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Surface::draw_aatrigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !aatrigonColor(surf, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Surface::draw_filled_trigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !filledTrigonColor(surf, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Surface::draw_polygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !polygonColor(surf, vx, vy, n, (uint32_t) color);
}
bool Surface::draw_aapolygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !aapolygonColor(surf, vx, vy, n, (uint32_t) color);
}
bool Surface::draw_filled_polygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !filledPolygonColor(surf, vx, vy, n, (uint32_t) color);
}
bool Surface::draw_bezier (const int16_t * vx, const int16_t * vy, int n, int s, Color color)
{
    return !bezierColor(surf, vx, vy, n, s, (uint32_t) color);
}

}
