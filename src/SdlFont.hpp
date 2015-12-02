#ifndef SDLFONT_HPP_INCLUDED
#define SDLFONT_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlRenderer.hpp"

#include <map>

namespace Sdl
{

class Font final
{
    void * membuffer;
    SDL_RWops * memcontent;

    mutable std::map<int, TTF_Font*> font_sizes;

    TTF_Font * get_font_by_size(int fontsize) const;

public:

    enum RenderMode
    {
        Solid = 1,
        Shaded = 2,
        Blended = 3,
    };

    Font() :
        membuffer{nullptr},
        memcontent{nullptr}
    { }

    Font(std::string filename);

    Font(Font const& old) = delete;
    Font& operator=(Font const& old) = delete;

    Font(Font&& old);

    Font& operator=(Font&& old);

    ~Font();

    Texture Render(Renderer& renderer, std::u16string text, int fontsize, Color color, Font::RenderMode mode, Color bgnd_color = Color{}) const;

};

}

#endif // SDLFONT_HPP_INCLUDED
