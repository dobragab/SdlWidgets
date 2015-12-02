#ifndef SDLFONT_HPP_INCLUDED
#define SDLFONT_HPP_INCLUDED

#include "Sdl.hpp"
#include "SdlRenderer.hpp"

namespace Sdl
{

class Font final
{
    TTF_Font * font = nullptr;

public:

    enum RenderMode
    {
        Solid = 1,
        Shaded = 2,
        Blended = 3,
    };

    Font() : font{nullptr}
    { }

    Font(std::string filename, int size);

    Font(Font const& old) = delete;
    Font& operator=(Font const& old) = delete;

    Font(Font&& old);

    Font& operator=(Font&& old);

    ~Font();

    Texture Render(Renderer& renderer, std::u16string text, Color color, Font::RenderMode mode, Color bgnd_color = Color{}) const;

};

}

#endif // SDLFONT_HPP_INCLUDED
