#include "SdlTheme.hpp"

#include "SdlWidgets.hpp"

namespace Sdl
{

Theme Widget::DefaultTheme
{
    Color(0x000000FF),
    Color(0xFFFFFF20),
    Color(0x101010FF),
    Color(0x00C0F0FF),
    new Font("micross.ttf"),
    size_t(16)
};

Theme Slider::DefaultTheme
{
    Widget::DefaultTheme.InnerBorderColor,
    Widget::DefaultTheme.OuterBorderColor,
    Widget::DefaultTheme.BaseColor,
    Color(0x00CCFF70),
    Widget::DefaultTheme.MainFont,
    Widget::DefaultTheme.FontSize
};

Theme ColorBox::DefaultTheme
{
    Widget::DefaultTheme.InnerBorderColor,
    Widget::DefaultTheme.OuterBorderColor,
    Widget::DefaultTheme.BaseColor,
    Color(0x000000FF),
    Widget::DefaultTheme.MainFont,
    Widget::DefaultTheme.FontSize
};

Color Window::DefaultColor(0x303030FF);

Point Widget::defloc = Point(0, 0);

Dimension Button::defsize = Dimension(75, 23);
Dimension Label::defsize = Dimension(0, 0);
Dimension Slider::defsize = Dimension(100, 23);
Dimension ColorBox::defsize = Dimension(128, 32);
Dimension TextBox::defsize = Dimension(128, 32);

}
