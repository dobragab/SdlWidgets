#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

namespace Sdl
{

Renderer::Renderer()
{ }

Renderer::Renderer(SDL_Renderer * renderer) :
    renderer{renderer}
{
    if(!renderer)
        throw Sdl::exception();
}

Renderer::Renderer(Renderer&& old) :
    renderer{old.renderer}
{
    old.renderer = nullptr;
}

Renderer& Renderer::operator=(Renderer&& old)
{
    if (this != &old)
    {
        SDL_DestroyRenderer(renderer);
        renderer = old.renderer;
        old.renderer = nullptr;
    }
    return *this;
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}

void Renderer::Blit(Texture const& src, std::nullptr_t, std::nullptr_t)
{
    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, nullptr, nullptr);
    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Blit(Texture const& src, Rect srcrect, Rect dstrect)
{
    SDL_Rect r1 = ConvertRect(srcrect);
    SDL_Rect r2 = ConvertRect(dstrect);

    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, &r1, &r2);
    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Blit(Texture const& src, std::nullptr_t, Rect dstrect)
{
    SDL_Rect r1 = ConvertRect(dstrect);

    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, nullptr, &r1);

    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Blit(Texture const& src, Rect srcrect, std::nullptr_t)
{
    SDL_Rect r1 = ConvertRect(srcrect);

    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, &r1, nullptr);

    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Fill(Rect area, Color c)
{
    SDL_Rect r1 = ConvertRect(area);

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &r1);
}

void Renderer::Fill(Color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
}

void Renderer::Flip()
{
    SDL_RenderPresent(renderer);
}

Renderer::operator SDL_Renderer*()
{   return renderer; }



// SDL_gfxPrimitives
bool Renderer::draw_pixel(int16_t x, int16_t y, Color color)
{
    return !pixelColor(renderer, x, y, (uint32_t) color);
}
bool Renderer::draw_hline (int16_t x1, int16_t x2, int16_t y, Color color)
{
    return !hlineColor(renderer, x1, x2, y, (uint32_t) color);
}
bool Renderer::draw_vline (int16_t x, int16_t y1, int16_t y2, Color color)
{
    return !vlineColor(renderer, x, y1, y2, (uint32_t) color);
}
bool Renderer::draw_rectangle (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !rectangleColor(renderer, x1, y1, x2, y2, (uint32_t) color);
}
bool Renderer::draw_rounded_rectangle (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color)
{
    return !roundedRectangleColor(renderer, x1, y1, x2, y2, rad, (uint32_t) color);
}
bool Renderer::draw_box (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !boxColor(renderer, x1, y1, x2, y2, (uint32_t) color);
}
bool Renderer::draw_rounded_box (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color)
{
    return !roundedBoxColor(renderer, x1, y1, x2, y2, rad, (uint32_t) color);
}
bool Renderer::draw_line (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !lineColor(renderer, x1, y1, x2, y2, (uint32_t) color);
}
bool Renderer::draw_aaline (int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color)
{
    return !aalineColor(renderer, x1, y1, x2, y2, (uint32_t) color);
}
bool Renderer::draw_thick_line (int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width, Color color)
{
    return !thickLineColor(renderer, x1, y1, x2, y2, width, (uint32_t) color);
}
bool Renderer::draw_circle (int16_t x, int16_t y, int16_t rad, Color color)
{
    return !circleColor(renderer, x, y, rad, (uint32_t) color);
}
bool Renderer::draw_arc (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !arcColor(renderer, x, y, rad, start, end, (uint32_t) color);
}
bool Renderer::draw_aacircle (int16_t x, int16_t y, int16_t rad, Color color)
{
    return !aacircleColor(renderer, x, y, rad, (uint32_t) color);
}
bool Renderer::draw_filled_circle (int16_t x, int16_t y, int16_t r, Color color)
{
    return !filledCircleColor(renderer, x, y, r, (uint32_t) color);
}
bool Renderer::draw_ellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !ellipseColor(renderer, x, y, rx, ry, (uint32_t) color);
}
bool Renderer::draw_aaellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !aaellipseColor(renderer, x, y, rx, ry, (uint32_t) color);
}
bool Renderer::draw_filled_ellipse (int16_t x, int16_t y, int16_t rx, int16_t ry, Color color)
{
    return !filledEllipseColor(renderer, x, y, rx, ry, (uint32_t) color);
}
bool Renderer::draw_pie (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !pieColor(renderer, x, y, rad, start, end, (uint32_t) color);
}
bool Renderer::draw_filled_pie (int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color)
{
    return !filledPieColor(renderer, x, y, rad, start, end, (uint32_t) color);
}
bool Renderer::draw_trigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !trigonColor(renderer, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Renderer::draw_aatrigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !aatrigonColor(renderer, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Renderer::draw_filled_trigon (int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color)
{
    return !filledTrigonColor(renderer, x1, y1, x2, y2, x3, y3, (uint32_t) color);
}
bool Renderer::draw_polygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !polygonColor(renderer, vx, vy, n, (uint32_t) color);
}
bool Renderer::draw_aapolygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !aapolygonColor(renderer, vx, vy, n, (uint32_t) color);
}
bool Renderer::draw_filled_polygon (const int16_t * vx, const int16_t * vy, int n, Color color)
{
    return !filledPolygonColor(renderer, vx, vy, n, (uint32_t) color);
}
bool Renderer::draw_bezier (const int16_t * vx, const int16_t * vy, int n, int s, Color color)
{
    return !bezierColor(renderer, vx, vy, n, s, (uint32_t) color);
}


}
