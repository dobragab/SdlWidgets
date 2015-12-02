#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Renderer::Renderer()
{ }

Renderer::Renderer(SDL_Renderer * renderer) :
    renderer{renderer}
{
//    if(!renderer)
//        throw Sdl::exception();
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

void Renderer::Blit(Texture const& src)
{
    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, nullptr, nullptr);
    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Blit(Texture const& src, Rect srcrect, Rect dstrect)
{
    int result = SDL_RenderCopy(renderer, (SDL_Texture*)src, srcrect, dstrect);
    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Blit(Texture const& src, Rect rect, bool dst)
{
    int result;
    if (dst)
        result = SDL_RenderCopy(renderer, (SDL_Texture*)src, rect, nullptr);
    else
        result = SDL_RenderCopy(renderer, (SDL_Texture*)src, nullptr, rect);

    if(result != 0)
        throw Sdl::exception();
}

void Renderer::Fill(Rect area, Color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, area);
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

}
