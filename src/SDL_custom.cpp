#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

namespace Sdl
{

SDL_Color ConvertColor(Color c)
{
    SDL_Color result;

    result.r = c.r;
    result.g = c.g;
    result.b = c.b;
    result.a = c.a;

    return result;
}
Color ConvertColor(SDL_Color c)
{
    Color result;

    result.r = c.r;
    result.g = c.g;
    result.b = c.b;
    result.a = c.a;

    return result;
}
SDL_Rect ConvertRect(Rect r)
{
    SDL_Rect result;

    result.x = r.x;
    result.y = r.y;
    result.w = r.w;
    result.h = r.h;

    return result;
}
Rect ConvertRect(SDL_Rect r)
{
    Rect result;

    result.x = r.x;
    result.y = r.y;
    result.w = r.w;
    result.h = r.h;

    return result;
}

SDL_RWops * SDL_RWFromFileToMemory(const char * filename, const char * mode, void *& bytebuffer)
{
    char * membuf = nullptr;
    SDL_RWops * memoryrw = nullptr;
    int64_t filesize = 0;

    SDL_RWops * filerw = SDL_RWFromFile(filename, mode);
    if (filerw == nullptr)
        goto fail1;

    filesize = SDL_RWsize(filerw);
    if (filesize < 0)
        goto fail2;

    membuf = (char*) malloc(filesize);
    if (membuf == nullptr)
        goto fail2;

    if (SDL_RWread(filerw, membuf,  filesize, 1) == 0)
        goto fail3;

    memoryrw = SDL_RWFromMem(membuf, filesize);
    if (memoryrw == nullptr)
        goto fail3;

    bytebuffer = membuf;

    SDL_RWclose(filerw);
    return memoryrw;

fail3:  free(membuf);
fail2:  SDL_RWclose(filerw);
fail1:  return nullptr;
}

}
