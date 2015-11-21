#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

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


Size Texture::size() const
{
    int w, h;
    int access;
    uint32_t format;

    int result = SDL_QueryTexture(txt, &format, &access, &w, &h);

    if(result != 0)
        throw Sdl::exception();

    return Size(w, h);
}

//Texture LoadImage(std::string filename)
//{
//    return Texture{IMG_LoadTexture(renderer, filename.c_str())};
//}

}
