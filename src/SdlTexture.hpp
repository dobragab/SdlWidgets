#ifndef SDLTEXTURE_HPP_INCLUDED
#define SDLTEXTURE_HPP_INCLUDED

namespace Sdl
{

class Renderer;
class Surface;

class Texture
{
    SDL_Texture * txt;

  public:

    Texture(Renderer& renderer, Surface& surface);

    explicit Texture(SDL_Texture * txt);
    Texture(Texture&& old);
    Texture& operator=(Texture&& old);

    Texture(const Texture& old) = delete;
    Texture& operator=(const Texture& old) = delete;

    ~Texture();

    explicit operator SDL_Texture*() const
    {
        return txt;
    }

    Dimension Size() const;
};

}

#endif // SDLTEXTURE_HPP_INCLUDED
