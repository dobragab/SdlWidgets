#ifndef SDLRENDERER_HPP_INCLUDED
#define SDLRENDERER_HPP_INCLUDED

#include "Sdl.hpp"

namespace Sdl
{

class Renderer
{
protected:
    SDL_Renderer * renderer = nullptr;

public:

    Renderer();
    Renderer(SDL_Renderer * renderer);

    Renderer(const Renderer& old) = delete;
    Renderer& operator=(const Renderer& old) = delete;

    Renderer(Renderer&& old);
    Renderer& operator=(Renderer&& old);

    virtual ~Renderer();

    void Blit(Texture const& src);
    void Blit(Texture const& src, Rect srcrect, Rect dstrect);
    void Blit(Texture const& src, Rect rect, bool dst);

    void Fill(Rect area, Color c);
    void Fill(Color c);

    int16_t width() const;
    int16_t height() const;
    SDL_PixelFormat * format() const;

    operator SDL_Renderer*();

    void Flip();

};

}

#endif // SDLRENDERER_HPP_INCLUDED
