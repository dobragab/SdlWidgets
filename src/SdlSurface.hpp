#ifndef SDLSURFACE_HPP_INCLUDED
#define SDLSURFACE_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

class Surface
{
protected:
    SDL_Surface * screen = nullptr;

public:

    Surface(SDL_Surface * screen);

    Surface(const Surface& old) = delete;
    Surface& operator=(const Surface& old) = delete;

    Surface(Surface&& old);
    Surface& operator=(Surface&& old);

    virtual ~Surface();

    void Blit(Surface const& src, Point srcrect, Rect& dstrect);
    void Blit(Surface const& src, Point srcrect);
    void Blit(Surface const& src, Rect& dstrect);
    void Blit(Surface const& src);

    void Fill(Rect area, Color c);
    void Fill(Color c);

    int16_t width() const;
    int16_t height() const;
    SDL_PixelFormat * format() const;

    operator SDL_Surface*();

    void Flip();

};

Surface LoadImage(std::string filename);

}

#endif // SDLSURFACE_HPP_INCLUDED
