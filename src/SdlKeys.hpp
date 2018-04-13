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

#include <type_traits>

namespace Sdl
{
    typedef decltype(SDLK_UNKNOWN) Keycode;
    using Keymod = SDL_Keymod;
    using Scancode = SDL_Scancode;

    template<typename Traits>
    struct SmartEnum : public Traits
    {
        using Enum = typename Traits::Enum;

        Enum value;

        SmartEnum() : value(0) {}
        SmartEnum(Enum e) : value(e) {}

        explicit SmartEnum(typename std::underlying_type<Enum>::type e) : value(Enum(e)) {}

        operator Enum&() { return value; }
        operator Enum const&() const { return value; }
    };

    struct MouseButtonTraits
    {
        enum Enum : uint8_t
        {
            None = 0,
            Left = 1,
            Middle = 2,
            Right = 3,
            X1 = 4,
            X2 = 5,
        };
    };
    using MouseButton = SmartEnum<MouseButtonTraits>;

    struct MouseButtonStateTraits
    {
#define SDL_BUTTON_DG(X)       (1 << ((X)-1))

        enum Enum : uint8_t
        {
            None = 0,
            Left = SDL_BUTTON_DG(1),
            Middle = SDL_BUTTON_DG(2),
            Right = SDL_BUTTON_DG(3),
            X1 = SDL_BUTTON_DG(4),
            X2 = SDL_BUTTON_DG(5),
        };

#undef SDL_BUTTON_DG
    };

    using MouseButtonState = SmartEnum<MouseButtonStateTraits>;

}

#endif // SDLKEYS_HPP_INCLUDED
