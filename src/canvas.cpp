#include <src/canvas.h>
#include <src/object.h>

Canvas::Canvas(int width, int height, bool scaleWithScreenSize)
{
    _width = width;
    _height = height;

    this->GetObject()->transform->position = glm::vec3(_width/2, _height/2, 0);

    _scaleWithScreenSize = scaleWithScreenSize;
}

Canvas::~Canvas()
{
}
