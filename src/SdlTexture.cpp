#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Texture::Texture(Renderer& renderer, Surface& surface) :
    txt{SDL_CreateTextureFromSurface((SDL_Renderer*)renderer, (SDL_Surface*)surface)}
{
    if (txt == nullptr)
        throw Sdl::exception();
}

Texture::Texture(SDL_Texture * txt) :
    txt{txt}
{
    if (!txt)
        throw Sdl::exception();
}

Texture::Texture(Texture&& old) :
    txt{old.txt}
{
    old.txt = nullptr;
}

Texture& Texture::operator=(Texture&& old)
{
    if (this != &old)
    {
        SDL_DestroyTexture(txt);
        txt = old.txt;
        old.txt = nullptr;
    }
    return *this;
}

Texture::~Texture()
{
    SDL_DestroyTexture(txt);
}


Dimension Texture::Size() const
{
    int w, h;
    int access;
    uint32_t format;

    int result = SDL_QueryTexture(txt, &format, &access, &w, &h);

    if(result != 0)
        throw Sdl::exception();

    return Dimension(w, h);
}

}
