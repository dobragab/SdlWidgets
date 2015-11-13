#include <cstdio>

#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"
#include <SDL.h>

int main ( int argc, char** argv )
{
try
{
    Sdl::Init(SDL_INIT_EVERYTHING);

    Sdl::Window::SetFont(Sdl::Font{"micross.ttf", 14});

    Sdl::Window screen(640, 480, SDL_HWSURFACE|SDL_DOUBLEBUF, "Sdl::Trial");

    Sdl::Button button1{L"Gomb"};

    screen.Add(button1);

    screen.ShowDialog();


}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
