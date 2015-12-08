#ifndef SDL_HPP_INCLUDED
#define SDL_HPP_INCLUDED

#include <stdexcept>
#include <cstdint>
#include <string>

struct SDL_Rect;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_RWops;
using TTF_Font = struct _TTF_Font ;

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


};

}

#endif // SDL_HPP_INCLUDED
