#ifndef SDLSURFACE_HPP_INCLUDED
#define SDLSURFACE_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

class Surface
{
    SDL_Surface * surf;

public:

    explicit Surface(SDL_Surface * surf);
    Surface(int width, int height);

    Surface(Surface&& old);
    Surface& operator=(Surface&& old);

    Surface(const Surface& old) = delete;
    Surface& operator=(const Surface& old) = delete;

    ~Surface();

    int Width() const;
    int Height() const;

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
