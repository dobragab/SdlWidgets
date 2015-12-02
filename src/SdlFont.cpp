#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

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

Texture Font::Render(Renderer& renderer, std::u16string text, Color color, Font::RenderMode mode, Color bgnd_color) const
{
    SDL_Surface * surf = nullptr;
    SDL_Color c = ConvertColor(color);

    const uint16_t * utext = reinterpret_cast<const uint16_t*>(text.c_str());

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

    if (!surf)
        throw Sdl::exception();

    SDL_Texture * txt = SDL_CreateTextureFromSurface((SDL_Renderer*)renderer, surf);

    SDL_FreeSurface(surf);

    if (!txt)
        throw Sdl::exception();

    return Texture{txt};
}

}
