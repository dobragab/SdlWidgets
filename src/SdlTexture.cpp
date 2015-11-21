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


//Texture LoadImage(std::string filename)
//{
//    return Texture{SDL_LoadTexture(filename.c_str())};
//}

}
