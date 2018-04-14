#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"
#include <SDL_gfx/SDL_gfxPrimitives.h>

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
    surf{SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)}
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

Surface Surface::ImgLoad(std::string const& filename)
{
    return Surface(IMG_Load(filename.c_str()));
}

void Surface::SaveJPG(std::string const& filename, int quality)
{
    if (IMG_SaveJPG(surf, filename.c_str(), quality) < 0)
        throw exception();
}

void Surface::SavePNG(std::string const& filename)
{
    if (IMG_SavePNG(surf, filename.c_str()) < 0)
        throw exception();
}

void Surface::SaveBMP(std::string const& filename)
{
    if (SDL_SaveBMP(surf, filename.c_str()) < 0)
        throw exception();
}

int Surface::Width() const
{
    return surf->w;
}

int Surface::Height() const
{
    return surf->h;
}

Dimension Surface::Size() const
{
    return Dimension(surf->w, surf->h);
}


uint8_t Surface::getAlphaMod() const
{
    uint8_t result;
    int res = SDL_GetSurfaceAlphaMod(surf, &result);
    if (res != 0)
        throw Sdl::exception();
    return result;
}

void Surface::setAlphaMod(uint8_t const& value)
{
    int res = SDL_SetSurfaceAlphaMod(surf, value);
    if (res != 0)
        throw Sdl::exception();
}

BlendMode Surface::getBlend() const
{
    SDL_BlendMode result;
    int res = SDL_GetSurfaceBlendMode(surf, &result);

    if (res != 0)
        throw Sdl::exception();

    return (BlendMode)result;
}

void Surface::setBlend(BlendMode const& value)
{
    SDL_BlendMode val = (SDL_BlendMode)value;
    int res = SDL_SetSurfaceBlendMode(surf, val);

    if (res != 0)
        throw Sdl::exception();
}

Color Surface::getColorMod() const
{
    Color c;
    int res = SDL_GetSurfaceColorMod(surf, &c.r, &c.g, &c.b);
    if (res != 0)
        throw Sdl::exception();
    return c;
}

void Surface::setColorMod(Color const& value)
{
    int res = SDL_SetSurfaceColorMod(surf, value.r, value.g, value.b);
    if (res != 0)
        throw Sdl::exception();
}

Rect Surface::getClipRect() const
{
    SDL_Rect result;
    SDL_GetClipRect(surf, &result);

    return ConvertRect(result);
}

void Surface::setClipRect(Rect const& value)
{
    SDL_Rect val = ConvertRect(value);
    int res = SDL_SetClipRect(surf, &val);
    if (res != 0)
        throw Sdl::exception();
}

void Surface::setClipRect(std::nullptr_t)
{
    int res = SDL_SetClipRect(surf, nullptr);
    if (res != 0)
        throw Sdl::exception();
}


void Surface::Blit(Surface const& src, Point srcrect, Rect dstrect)
{
    SDL_Rect srcr{srcrect.x, srcrect.y, 0, 0};
    SDL_Rect dstr = ConvertRect(dstrect);
    int result = SDL_UpperBlit(src.surf, &srcr, surf, &dstr);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src, Point srcrect)
{
    SDL_Rect srcr{srcrect.x, srcrect.y, 0, 0};
    int result = SDL_UpperBlit(src.surf, &srcr, surf, nullptr);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src, Rect dstrect)
{
    SDL_Rect dstr = ConvertRect(dstrect);
    int result = SDL_UpperBlit(src.surf, nullptr, surf, &dstr);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src)
{
    int result = SDL_UpperBlit(src.surf, nullptr, surf, nullptr);

    if(result != 0)
        throw Sdl::exception();
}

void Surface::Stretch(Surface const& src, std::nullptr_t, std::nullptr_t)
{
    int result = SDL_UpperBlitScaled(surf, nullptr, src.surf, nullptr);
    if(result != 0)
        throw Sdl::exception();
}

void Surface::Stretch(Surface const& src, Rect srcrect, std::nullptr_t)
{
    SDL_Rect r1 = ConvertRect(srcrect);

    int result = SDL_UpperBlitScaled(surf, &r1, src.surf, nullptr);

    if(result != 0)
        throw Sdl::exception();
}

void Surface::Stretch(Surface const& src, std::nullptr_t, Rect dstrect)
{
    SDL_Rect r1 = ConvertRect(dstrect);

    int result = SDL_UpperBlitScaled(surf, nullptr, src.surf, &r1);

    if(result != 0)
        throw Sdl::exception();
}

void Surface::Stretch(Surface const& src, Rect srcrect, Rect dstrect)
{
    SDL_Rect r1 = ConvertRect(srcrect);
    SDL_Rect r2 = ConvertRect(dstrect);

    int result = SDL_UpperBlitScaled(surf, &r1, src.surf, &r2);
    if(result != 0)
        throw Sdl::exception();
}

void Surface::Fill(Rect area, Color c)
{
    SDL_Rect a = ConvertRect(area);
    int result = SDL_FillRect(surf, &a, SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a));

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Fill(Color c)
{
    int result = SDL_FillRect(surf, nullptr, SDL_MapRGBA(surf->format, c.r, c.g, c.b, c.a));

    if(result != 0)
        throw Sdl::exception();
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
