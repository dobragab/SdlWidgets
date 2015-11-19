#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Surface LoadImage(std::string filename)
{
    return Surface{IMG_Load(filename.c_str())};
}


Surface::Surface(SDL_Surface * screen) :
    screen{screen}
{
    if(!screen)
        throw Sdl::exception();
}

Surface::Surface(Surface&& old) :
    screen{old.screen}
{
    old.screen = nullptr;
}

Surface& Surface::operator=(Surface&& old)
{
    if (this != &old)
    {
        SDL_FreeSurface(old.screen);
        screen = old.screen;
        old.screen = nullptr;
    }
    return *this;
}

Surface::~Surface()
{
    SDL_FreeSurface(screen);
}

void Surface::Blit(Surface const& src, Point srcrect, Rect& dstrect)
{
    Rect srcr{srcrect.x, srcrect.y, 0, 0};
    int result = SDL_UpperBlit(src.screen, srcr, screen, dstrect);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src, Point srcrect)
{
    Rect srcr{srcrect.x, srcrect.y, 0, 0};
    int result = SDL_UpperBlit(src.screen, srcr, screen, nullptr);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src, Rect& dstrect)
{
    int result = SDL_UpperBlit(src.screen, nullptr, screen, dstrect);

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Blit(Surface const& src)
{
    int result = SDL_UpperBlit(src.screen, nullptr, screen, nullptr);

    if(result != 0)
        throw Sdl::exception();
}

void Surface::Fill(Rect area, Color c)
{
    int result = SDL_FillRect(screen, area, SDL_MapRGBA(screen->format, c.r, c.g, c.b, c.a));

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Fill(Color c)
{
    int result = SDL_FillRect(screen, nullptr, SDL_MapRGBA(screen->format, c.r, c.g, c.b, c.a));

    if(result != 0)
        throw Sdl::exception();
}
void Surface::Flip()
{
    int result = SDL_Flip(screen);

    if(result != 0)
        throw Sdl::exception();
}
int16_t Surface::width() const
{   return screen->w; }

int16_t Surface::height() const
{   return screen->h; }

SDL_PixelFormat * Surface::format() const
{   return screen->format; }

Surface::operator SDL_Surface*()
{   return screen; }

}
