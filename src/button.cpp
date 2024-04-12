#include <src/button.h>

Button::Button()
{
    _width = 0;
    _height = 0;
    std::cout << "Creating Button from default constructor" << "\n";
}
Button::Button(int width, int height)
{
    _width = width;
    _height = height;
    std::cout << "Creating Button from overloaded constructor" << "\n";
}

Button::~Button()
{
    //dtor
}
