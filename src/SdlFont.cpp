#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

Font::Font(std::string filename) :
    membuffer{nullptr},
    memcontent{SDL_RWFromFileToMemory(filename.c_str(), "rb", membuffer)}
{
    if(!memcontent)
        throw Sdl::exception();
}

Font::Font(Font&& old) :
    membuffer{old.membuffer},
    memcontent{old.memcontent},
    font_sizes{std::move(old.font_sizes)}
{
    old.membuffer = nullptr;
    old.memcontent = nullptr;
}

Font& Font::operator=(Font&& old)
{
    if (&old != this)
    {
        if (memcontent != nullptr)
            SDL_RWclose(memcontent);
        free(membuffer);

        membuffer = old.membuffer;
        memcontent = old.memcontent;
        font_sizes = std::move(old.font_sizes);

        old.membuffer = nullptr;
        old.memcontent = nullptr;
    }
    return *this;
}

Font::~Font()
{
    if (memcontent != nullptr)
        SDL_RWclose(memcontent);
    free(membuffer);
}

TTF_Font * Font::get_font_by_size(size_t fontsize) const
{
    auto it = font_sizes.find(fontsize);
    if (it != font_sizes.end())
        return it->second;

    TTF_Font * font = TTF_OpenFontRW(memcontent, false, fontsize);

    font_sizes[fontsize] = font;

    return font;
}

Surface Font::Render(std::string text, size_t fontsize, Color color, Font::RenderMode mode, Color bgnd_color) const
{
    if(text.length() == 0)
        return Surface{1, 1};

    SDL_Surface * surf = nullptr;
    SDL_Color c = ConvertColor(color);
    TTF_Font * font = get_font_by_size(fontsize);

    switch(mode)
    {
        case Font::Solid:
            surf = TTF_RenderUTF8_Solid(font, text.c_str(), c);
            break;
        case Font::Shaded:
        {
            SDL_Color bgnd = ConvertColor(bgnd_color);
            surf = TTF_RenderUTF8_Shaded(font, text.c_str(), c, bgnd );
            break;
        }
        case Font::Blended:
            surf = TTF_RenderUTF8_Blended(font, text.c_str(), c);
            break;

        default:
            break;
    }

    return Surface{surf};
}


Texture Font::Render(Renderer& renderer, std::string text, size_t fontsize, Color color, Font::RenderMode mode, Color bgnd_color) const
{
    Surface surf = Render(text, fontsize, color, mode, bgnd_color);

    return Texture{renderer, surf};
}

Point Font::RenderSize(std::string text, size_t fontsize) const
{
    TTF_Font * font = get_font_by_size(fontsize);

    int x, y;

    TTF_SizeUTF8(font, text.c_str(), &x, &y);

    return Point(x, y);
}

}
