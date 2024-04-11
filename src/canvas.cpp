#include "src/component.h"
#include "src/config.h"
#include <src/canvas.h>
#include <src/object.h>

Canvas::Canvas(int width, int height) : Component()
{
    _width = width;
    _height = height;

    _referenceResolution = glm::vec2(width, height);

    _scaleWithScreenSize = false;
}

Canvas::Canvas(glm::vec2 referenceResolution)
{
    _width = Config::ScreenWidth;
    _height = Config::ScreenHeight;

    _scaleWithScreenSize = true;
    _referenceResolution = referenceResolution;
}

Canvas::~Canvas()
{
}
