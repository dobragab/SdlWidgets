#ifndef SDL_HPP_INCLUDED
#define SDL_HPP_INCLUDED

#include <stdexcept>
#include <cstdint>
#include <string>

#include "SdlKeys.hpp"

struct SDL_Rect;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_RWops;
struct _TTF_Font;

namespace Sdl {

void Init();
void PushEvent(uint8_t type, void * data1 = nullptr, void * data2 = nullptr);

struct exception : std::runtime_error
{
    using std::runtime_error::runtime_error;

    exception();
};

struct Point
{
    int16_t x = 0, y = 0;

    Point(int16_t x, int16_t y) :
        x(x),
        y(y)
    { }
};

inline Point operator+(Point p1, Point p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

inline Point operator-(Point p1, Point p2)
{
    return Point(p1.x +- p2.x, p1.y - p2.y);
}

struct Dimension
{
    uint16_t w = 0, h = 0;
    Dimension(uint16_t w, uint16_t h) :
        w(w),
        h(h)
    { }
};

struct Rect
{
    // DO NOT CHANGE, KEEP MEMORY LAYOUT OF SDL_Rect!
    int x, y;
    int w, h;

    Rect() :
        x(0), y(0), w(0), h(0)
    { }

    Rect(int x, int y, int w = 0, int h = 0) :
        x(x), y(y), w(w), h(h)
    { }

    Rect(Point p, Dimension d)
        : x(p.x), y(p.y), w(d.w), h(d.h)
    { }
};

struct Color
{
    uint8_t r, g, b, a;

    Color() :
        r{0x00}, g{0x00}, b{0x00}, a{0xFF}
    { }

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) :
        r{r}, g{g}, b{b}, a{a}
    { }

    explicit Color(uint32_t c) :
        r((c & 0xFF000000) >> 24),
        g((c & 0x00FF0000) >> 16),
        b((c & 0x0000FF00) >> 8),
        a((c & 0x000000FF) >> 0)
    { }

    explicit operator uint32_t() const
    {
        return  r << 24 |
                g << 16 |
                b << 8  |
                a;
    }

    static Color Transition(Color Primary, Color Secondary, double ratio);

};

enum class BlendMode
{
    None  = 0x00000000, // SDL_BLENDMODE_NONE
    Blend = 0x00000001, // SDL_BLENDMODE_BLEND
    Add   = 0x00000002, // SDL_BLENDMODE_ADD
    Mod   = 0x00000004, // SDL_BLENDMODE_MOD
};

}

#endif // SDL_HPP_INCLUDED
