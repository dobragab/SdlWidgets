#ifndef SDLKEYS_HPP_INCLUDED
#define SDLKEYS_HPP_INCLUDED

#ifndef SDL_stdinc_h_
#define SDL_stdinc_h_ // prevent SDL_stdinc.h include
#else
#define SDL_stdinc_h_EXISTED
#endif

#define Sint32 int32_t

#include <SDL2/SDL_keycode.h>

#undef Sint32

#ifndef SDL_stdinc_h_EXISTED
#undef SDL_stdinc_h_
#endif

#if defined(__GNUC__) && __GNUC__ >= 6
#pragma GCC diagnostic ignored "-Wsubobject-linkage"
#endif

namespace Sdl
{
    typedef decltype(SDLK_UNKNOWN) Keycode;
    using Keymod = SDL_Keymod;
    using Scancode = SDL_Scancode;
}

#endif // SDLKEYS_HPP_INCLUDED
