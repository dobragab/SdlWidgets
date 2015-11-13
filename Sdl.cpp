#include "Sdl.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_gfxPrimitives.h>

namespace Sdl
{

SDL_Color ConvertColor(Color c)
{
    SDL_Color result;

    result.r = c.r;
    result.g = c.g;
    result.b = c.b;
    result.unused = c.a;

    return result;
}

exception::exception() :
    std::runtime_error(SDL_GetError())
{ }

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


Font::Font(std::string filename, int size) :
    font{TTF_OpenFont(filename.c_str(), size)}
{
    if(!font)
        throw Sdl::exception();
}
Font::Font(Font&& old) :
    font{old.font}
{
    old.font = nullptr;
}
Font& Font::operator=(Font&& old)
{
    if (&old != this)
    {
        TTF_CloseFont(font);
        font = old.Font::font;
        old.font = nullptr;
    }
    return *this;
}
Font::~Font()
{
    TTF_CloseFont(font);
}

static constexpr bool wunicode = (sizeof(wchar_t) == sizeof(uint16_t));

Surface Font::Render(std::wstring text, Color color, Font::RenderMode mode, Color bgnd_color) const
{
    SDL_Surface * surf = nullptr;
    SDL_Color c = ConvertColor(color);

    const uint16_t * utext = nullptr;
    std::basic_string<uint16_t> * ustr = nullptr;

    if(wunicode)
        utext = reinterpret_cast<const uint16_t*>(text.c_str());
    else
    {
        ustr = new std::basic_string<uint16_t>{text.begin(), text.end()};
        utext = ustr->c_str();
    }

    switch(mode)
    {
        case Font::Solid:
            surf = TTF_RenderUNICODE_Solid(font, utext, c);
            break;
        case Font::Shaded:
        {
            SDL_Color bgnd = ConvertColor(bgnd_color);
            surf = TTF_RenderUNICODE_Shaded(font, utext, c, bgnd );
            break;
        }
        case Font::Blended:
            surf = TTF_RenderUNICODE_Blended(font, utext, c);
            break;

        default:
            break;
    }

    if (!wunicode)
        free(ustr);

    if (!surf)
        throw Sdl::exception();

    return Surface{surf};
}





void Init(uint32_t flags)
{
    int result = SDL_Init(flags);

    if (result < 0)
        throw Sdl::exception();

    atexit(SDL_Quit);

    TTF_Init();
    SDL_EnableUNICODE(true);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

Surface LoadImage(std::string filename)
{
    return Surface{IMG_Load(filename.c_str())};
}

}
