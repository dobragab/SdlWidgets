#ifndef SDLFONT_HPP_INCLUDED
#define SDLFONT_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlRenderer.hpp"

#include <map>

namespace Sdl
{

class Font final
{
public:

    enum RenderMode
    {
        Solid = 1,
        Shaded = 2,
        Blended = 3,
    };

    enum RenderStyle
    {
        Normal = 0,
        Bold = 1,
        Italic = 2,
        Underline = 4,
        Strikethrough = 8,
    };

private:
    void * membuffer;
    SDL_RWops * memcontent;

    mutable std::map<size_t, _TTF_Font*> font_sizes;

    _TTF_Font * get_font_by_size(size_t fontsize, RenderStyle style) const;

public:
    Font() :
        membuffer{nullptr},
        memcontent{nullptr}
    { }

    explicit Font(std::string const& filename);

    Font(Font const& old) = delete;
    Font& operator=(Font const& old) = delete;

    Font(Font&& old);
    Font& operator=(Font&& old);

    ~Font();

    Surface Render(std::string const& text, size_t fontsize, Color color, RenderMode mode = Blended, RenderStyle style = Normal, Color bgnd_color = Color{}) const;
    Texture Render(Renderer& renderer, std::string const& text, size_t fontsize, Color color, RenderMode mode = Blended, RenderStyle style = Normal, Color bgnd_color = Color{}) const;

    Dimension RenderSize(std::string const& text, size_t fontsize, RenderStyle style = Normal) const;

};

}

#endif // SDLFONT_HPP_INCLUDED
