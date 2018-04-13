#include <cstdio>
#include <sstream>

#include "SdlWidgets.hpp"

Sdl::WidgetWindow * screenptr;
Sdl::Button button1;
Sdl::Button button2;
Sdl::Label label1;
Sdl::Label label2;
Sdl::Slider slider1;
Sdl::ColorBox box;
Sdl::TextBox textbox;
Sdl::TextBox textbox2;

void button1_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    screenptr->SetFocus(&textbox);
}

void button2_MouseClicked(Sdl::Widget& sender, Sdl::MouseClickEvent& ev)
{
    button1.Visible = !button1.Visible;
}

void slider_ValueChanged(Sdl::Widget& sender, Sdl::ValueChangedEvent<int>& ev)
{
    Sdl::Slider& slider = dynamic_cast<Sdl::Slider&>(sender);
    label2.Text = std::to_string(slider.Value);
    box.DisplayedColor = Sdl::Color(slider1.Value, 0, 0 );
}

void textbox_TextChanged(Sdl::Widget& sender, Sdl::TextChangedEvent& ev)
{
    label1.Text = textbox.Text;
}

void textbox2_TextChanged(Sdl::Widget& sender, Sdl::TextChangedEvent& ev)
{
    label1.Text = textbox2.Text;
}


int main(int argc, char **argv)
{
try
{
    Sdl::Init();
    Sdl::WidgetWindow screen(Sdl::Dimension(640, 480), "Sdl::Trial");
    screenptr = &screen;

    button1.Text = "Gomb";
    button1.Size = Sdl::Dimension(75, 40);
    button1.Location = Sdl::Point(100, 100);
    button1.MouseClicked = button1_MouseClicked;

    button2.Text = "Csere";
    button2.Size = Sdl::Dimension(75, 40);
    button2.Location = Sdl::Point(150, 100);
    button2.MouseClicked = button2_MouseClicked;

    slider1.Location = Sdl::Point(100, 150);
    slider1.Size = Sdl::Dimension(100, 23);
    slider1.Value = 0;
    slider1.Maximum = 255;
    slider1.ValueChanged = slider_ValueChanged;

    label1.Text = "Árvíztűrő tükörfúrógép";
    label1.Location = Sdl::Point(100, 80);

    label2.Text = std::to_string(slider1.Value);
    label2.Location = Sdl::Point(210, 150);

    box.Location = Sdl::Point(100, 250);
    box.DisplayedColor = Sdl::Color(slider1.Value, 0, 0);

    textbox.Location = Sdl::Point(100, 185);
    textbox.Size = Sdl::Dimension(100, 23);
    textbox.Text = "Default";
    textbox.TextChanged = textbox_TextChanged;

    textbox2.Location = Sdl::Point(100, 215);
    textbox2.Size = Sdl::Dimension(100, 23);
    textbox2.Text = "Default2";
    textbox2.TextChanged = textbox2_TextChanged;

    screen.Add(button1);
    screen.Add(button2);
    screen.Add(label1);
    screen.Add(slider1);
    screen.Add(label2);
    screen.Add(box);
    screen.Add(textbox);
    screen.Add(textbox2);

    screen.ShowDialog();
}
catch(Sdl::exception x)
{
    puts(x.what());
}

    return 0;
}
