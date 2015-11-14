#include <cstdio>
#include <sstream>

#include "Sdl.hpp"
#include "SdlWidget.hpp"
#include "SdlWindow.hpp"

template<typename T>
std::string ToString(T const& val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

template<typename T>
std::wstring ToWString(T const& val)
{
    std::wostringstream oss;
    oss << val;
    return oss.str();
}


Sdl::Button button1;
Sdl::Button button2;
Sdl::Label label1;
Sdl::Label label2;
Sdl::Slider slider1;

void button1_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button2.Visible = !button2.Visible;
}

void button2_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button1.Visible = !button1.Visible;
}

void slider_ValueChanged(Sdl::Widget& sender)
{
    Sdl::Slider& slider = dynamic_cast<Sdl::Slider&>(sender);
    label2.Text = ToWString(slider.Value);
}


int main(int argc, char **argv)
{
try
{
    Sdl::Init();
    Sdl::SetFont(Sdl::Font{"micross.ttf", 16});
    Sdl::Window screen(640, 480, "Sdl::Trial");

    button1.Text = L"Gomb";
    button1.size = Sdl::Size(75, 40);
    button1.Location = Sdl::Point(100, 100);
    button1.MouseClicked = button1_MouseClicked;

    button2.Text = L"Csere";
    button2.size = Sdl::Size(75, 40);
    button2.Location = Sdl::Point(150, 100);
    button2.MouseClicked = button2_MouseClicked;

    slider1.Location = Sdl::Point(100, 150);
    slider1.size = Sdl::Size(100, 23);
    slider1.Value = 0;
    slider1.Maximum = 255;
    slider1.ValueChanged = slider_ValueChanged;

    label1.Text = L"Felirat";
    label1.Location = Sdl::Point(100, 80);

    label2.Text = L" ";
    label2.Location = Sdl::Point(210, 150);

    screen.Add(button1);
    screen.Add(button2);
    screen.Add(label1);
    screen.Add(slider1);
    screen.Add(label2);

    screen.ShowDialog();
}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
