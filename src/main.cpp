#include <cstdio>
#include <sstream>

#include "SdlWidgets.hpp"

template<typename T>
std::string ToString(T const& val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

template<typename T>
std::u16string Tou16string(T const& val)
{
    std::wstringstream oss;
    oss << val;
    std::wstring ws = oss.str();
    return std::u16string{ws.begin(), ws.end()};
}


Sdl::Button button1;
Sdl::Button button2;
Sdl::Label label1;
Sdl::Label label2;
Sdl::Slider slider1;
Sdl::ColorBox box;
Sdl::TextBox textbox;

void button1_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button2.Visible = !button2.Visible;
}

void button2_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button1.Visible = !button1.Visible;
}

void slider_ValueChanged(Sdl::Widget& sender, Sdl::ValueChangedEvent<int>& ev)
{
    Sdl::Slider& slider = dynamic_cast<Sdl::Slider&>(sender);
    label2.Text = Tou16string(slider.Value);
    box.DisplayedColor = Sdl::Color(slider1.Value, 0, 0 );
}

void textbox_TextChanged(Sdl::Widget& sender, Sdl::TextChangedEvent& ev)
{
    label1.Text = textbox.Text;
}


int main(int argc, char **argv)
{
try
{
    Sdl::Init();
    Sdl::SetFont(Sdl::Font{"micross.ttf"});
    Sdl::Window screen(640, 480, "Sdl::Trial");

    button1.Text = u"Gomb";
    button1.Size = Sdl::Dimension(75, 40);
    button1.Location = Sdl::Point(100, 100);
    button1.MouseClicked = button1_MouseClicked;

    button2.Text = u"Csere";
    button2.Size = Sdl::Dimension(75, 40);
    button2.Location = Sdl::Point(150, 100);
    button2.MouseClicked = button2_MouseClicked;

    slider1.Location = Sdl::Point(100, 150);
    slider1.Size = Sdl::Dimension(100, 23);
    slider1.Value = 0;
    slider1.Maximum = 255;
    slider1.ValueChanged = slider_ValueChanged;

    label1.Text = u"Árvíztűrő tükörfúrógép";
    label1.Location = Sdl::Point(100, 80);

    label2.Text = Tou16string(slider1.Value);
    label2.Location = Sdl::Point(210, 150);

    box.Location = Sdl::Point(100, 250);
    box.DisplayedColor = Sdl::Color(slider1.Value, 0, 0);

    textbox.Location = Sdl::Point(100, 200);
    textbox.Size = Sdl::Dimension(100, 23);
    textbox.Text = u"Default";
    textbox.TextChanged = textbox_TextChanged;

    screen.Add(button1);
    screen.Add(button2);
    screen.Add(label1);
    screen.Add(slider1);
    screen.Add(label2);
    screen.Add(box);
    screen.Add(textbox);

    screen.ShowDialog();
}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
