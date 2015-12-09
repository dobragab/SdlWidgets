#ifndef SDLSURFACE_HPP_INCLUDED
#define SDLSURFACE_HPP_INCLUDED

#include "Sdl.hpp"
#include "Property.hpp"
#include "PropertyNull.hpp"

namespace Sdl
{

class Surface
{
    SDL_Surface * surf;

    Rect getClipRect() const;
    void setClipRect(Rect const&);
    void setClipRect(std::nullptr_t);

    uint8_t getAlphaMod() const;
    void setAlphaMod(uint8_t const&);

    BlendMode getBlend() const;
    void setBlend(BlendMode const&);

    Color getColorMod() const;
    void setColorMod(Color const&);

public:

    PROPERTYNULL(Surface, Rect, ClipRect);
    PROPERTY(Surface, uint8_t, AlphaMod);
    PROPERTY(Surface, BlendMode, Blend);
    PROPERTY(Surface, Color, ColorMod);

    explicit Surface(SDL_Surface * surf);
    Surface(int width, int height);

    Surface(Surface&& old);
    Surface& operator=(Surface&& old);

    Surface(const Surface& old) = delete;
    Surface& operator=(const Surface& old) = delete;

    ~Surface();

    int Width() const;
    int Height() const;
    Dimension Size() const;

    void Blit(Surface const& src, Point srcrect, Rect dstrect);
    void Blit(Surface const& src, Point srcrect);
    void Blit(Surface const& src, Rect  dstrect);
    void Blit(Surface const& src);

    void Stretch(Surface const& src, std::nullptr_t = nullptr, std::nullptr_t = nullptr);
    void Stretch(Surface const& src, Rect srcrect, std::nullptr_t = nullptr);
    void Stretch(Surface const& src, std::nullptr_t, Rect dstrect);
    void Stretch(Surface const& src, Rect srcrect, Rect dstrect);

    void Fill(Rect area, Color c);
    void Fill(Color c);

    explicit operator SDL_Surface*() const;

// SDL_gfxPrimitives

	bool draw_pixel(int16_t x, int16_t y, Color color);
	bool draw_hline(int16_t x1, int16_t x2, int16_t y, Color color);
	bool draw_vline(int16_t x, int16_t y1, int16_t y2, Color color);
	bool draw_rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color);
	bool draw_rounded_rectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color);
	bool draw_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color);
	bool draw_rounded_box(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad, Color color);
	bool draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color);
	bool draw_aaline(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color);
	bool draw_thick_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width, Color color);
	bool draw_circle(int16_t x, int16_t y, int16_t rad, Color color);
	bool draw_arc(int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color);
	bool draw_aacircle(int16_t x, int16_t y, int16_t rad, Color color);
	bool draw_filled_circle(int16_t x, int16_t y, int16_t r, Color color);
	bool draw_ellipse(int16_t x, int16_t y, int16_t rx, int16_t ry, Color color);
	bool draw_aaellipse(int16_t x, int16_t y, int16_t rx, int16_t ry, Color color);
	bool draw_filled_ellipse(int16_t x, int16_t y, int16_t rx, int16_t ry, Color color);
	bool draw_pie(int16_t x, int16_t y, int16_t rad, int16_t start, int16_t end, Color color);
	bool draw_filled_pie(int16_t x, int16_t y, int16_t rad,	int16_t start, int16_t end, Color color);
	bool draw_trigon(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color);
	bool draw_aatrigon(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color);
	bool draw_filled_trigon(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, Color color);
	bool draw_polygon(const int16_t * vx, const int16_t * vy, int n, Color color);
	bool draw_aapolygon(const int16_t * vx, const int16_t * vy, int n, Color color);
	bool draw_filled_polygon(const int16_t * vx, const int16_t * vy, int n, Color color);
	bool draw_bezier(const int16_t * vx, const int16_t * vy, int n, int s, Color color);
};


}

#endif // SDLSURFACE_HPP_INCLUDED
