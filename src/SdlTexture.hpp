#ifndef SDLTEXTURE_HPP_INCLUDED
#define SDLTEXTURE_HPP_INCLUDED

namespace Sdl
{

class Texture
{
    SDL_Texture * txt;

  public:

    Texture(SDL_Texture * txt);
    Texture(Texture&& old);
    Texture& operator=(Texture&& old);

    Texture(const Texture& old) = delete;
    Texture& operator=(const Texture& old) = delete;

    ~Texture();

    explicit operator SDL_Texture*()
    {
        return txt;
    }
};

//Texture LoadImage(std::string filename);

}

#endif // SDLTEXTURE_HPP_INCLUDED
