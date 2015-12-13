#include "SdlTheme.hpp"

#include "SdlWidgets.hpp"

namespace Sdl
{

Theme WidgetTheme
{
    Color(0x000000FF),
    Color(0xFFFFFF20),
    Color(0x101010FF),
    Color(0x00C0F0FF),
    new Font("micross.ttf"),
    int(16)
};

Theme SliderTheme
{
    WidgetTheme.InnerBorderColor,
    WidgetTheme.OuterBorderColor,
    WidgetTheme.BaseColor,
    Color(0x00FFFF50),
    WidgetTheme.MainFont,
    WidgetTheme.FontSize
};


Theme ColorBoxTheme
{
    WidgetTheme.InnerBorderColor,
    WidgetTheme.OuterBorderColor,
    WidgetTheme.BaseColor,
    Color(0x000000FF),
    WidgetTheme.MainFont,
    WidgetTheme.FontSize
};

Dimension Button::defsize = Dimension(75, 23);
Dimension Label::defsize = Dimension(0, 0);
Dimension Slider::defsize = Dimension(100, 23);
Dimension ColorBox::defsize = Dimension(128, 32);
Dimension TextBox::defsize = Dimension(128, 32);
Point Widget::defloc = Point(0, 0);
Color Window::BackgroundColor(0x303030FF);

}
