#ifndef SDLRENDERER_HPP_INCLUDED
#define SDLRENDERER_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlTexture.hpp"

namespace Sdl
{

class Renderer
{
protected:
    SDL_Renderer * renderer = nullptr;

public:

    Renderer();
    explicit Renderer(SDL_Renderer * renderer);

    Renderer(const Renderer& old) = delete;
    Renderer& operator=(const Renderer& old) = delete;

    Renderer(Renderer&& old);
    Renderer& operator=(Renderer&& old);

    ~Renderer();

    void Blit(Texture const& src);
    void Blit(Texture const& src, Rect srcrect, Rect dstrect);
    void Blit(Texture const& src, Rect rect, bool dst);

    void Fill(Rect area, Color c);
    void Fill(Color c);

    explicit operator SDL_Renderer*();

    void Flip();

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

#endif // SDLRENDERER_HPP_INCLUDED
