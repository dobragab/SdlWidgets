#include <cstdio>

#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"
#include <SDL.h>

int main(int argc, char **argv)
{
try
{
    Sdl::Init();
    Sdl::Window::SetFont(Sdl::Font{"micross.ttf", 14});
    Sdl::Window screen(640, 480, "Sdl::Trial");

    Sdl::Button button1{L"Gomb"};

    button1.size = Sdl::Size(75, 40);
    button1.Location = Sdl::Point(100, 100);
    button1.Text = L"Bullshit";

    screen.Add(button1);

    screen.ShowDialog();
}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
