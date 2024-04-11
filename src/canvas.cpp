#include "src/component.h"
#include <src/canvas.h>
#include <src/object.h>

Canvas::Canvas(int width, int height, bool scaleWithScreenSize) : Component()
{
    _width = width;
    _height = height;

    _scaleWithScreenSize = scaleWithScreenSize;
}

Canvas::~Canvas()
{
}
