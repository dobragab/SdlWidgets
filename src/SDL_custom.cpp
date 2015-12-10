#include "SdlWidgets.hpp"

#include "SDL_custom.hpp"

#include <sstream>

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

std::u16string utf8_2_unicode(uint8_t const *be) {
    std::basic_ostringstream<char16_t> boss;
    int pb;

    for (pb=0; be[pb]!=0; ++pb) {
        if (be[pb]<0x80) {
            /* 00000000 0xxxxxxx    0x0000-0x007F    0xxxxxxx */
            boss << (char16_t)be[pb];
        }
        else
        if (be[pb]>>5 == 6) {   /* 0x6 = 110 bin */
            /* 00000yyy yyxxxxxx    0x0080-0x07FF    110yyyyy 10xxxxxx */
            boss << (char16_t)((be[pb]&0x1f)<<6 | (be[pb+1]&0x3f));
            pb+=1;              /* ket bajtot hasznaltunk */
        }
        else {
            /* zzzzyyyy yyxxxxxx    0x0800-0xFFFF   1110zzzz 10yyyyyy 10xxxxxx */
            boss << (char16_t)((be[pb]&0x0f)<<12 | (be[pb+1]&0x3f)<<6 | (be[pb+2]&0x3f));
            pb+=2;              /* harom bajtot hasznaltunk */
        }
    }

    return boss.str();
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
