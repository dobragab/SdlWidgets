#include <cstdio>

#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"
#include <SDL.h>

Sdl::Button button1;
Sdl::Button button2;

void button1_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    //button2.Text = L"Lecseréltem!";
    button2.Visible = !button2.Visible;
}

void button2_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button1.Visible = !button1.Visible;
}


int main(int argc, char **argv)
{
try
{
    Sdl::Init();
    Sdl::SetFont(Sdl::Font{"micross.ttf", 14});
    Sdl::Window screen(640, 480, "Sdl::Trial");


    button1.Text = L"Gomb";
    button1.size = Sdl::Size(75, 40);
    button1.Location = Sdl::Point(100, 100);

    //button1.MouseClicked = button1_MouseClicked;

    button2.Text = L"Csere";
    button2.size = Sdl::Size(75, 40);
    button2.Location = Sdl::Point(150, 100);

    //button2.MouseClicked = button2_MouseClicked;

    screen.Add(button1);
    screen.Add(button2);

    screen.ShowDialog();
}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
