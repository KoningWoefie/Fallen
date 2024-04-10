#ifndef CANVAS_H
#define CANVAS_H

#include "src/config.h"
#include <src/component.h>

class Canvas : public Component
{
public:
    Canvas(int width = Config::ScreenWidth, int height = Config::ScreenHeight, bool scaleWithScreenSize = true);
    virtual ~Canvas();

    glm::vec2 GetCanvasSize() { return glm::vec2(_width, _height); };

    int GetCanvasWidth() { return _width; };
    int GetCanvasHeight() { return _height; };

    void SetCanvasSize(int width, int height) { _width = width; _height = height; };

    void SetCanvasWidth(int width) { _width = width; };
    void SetCanvasHeight(int height) { _height = height; };

    void SetScaleWithScreenSize(bool scale) { _scaleWithScreenSize = scale; };
    bool GetScaleWithScreenSize() { return _scaleWithScreenSize; };

private:
    int _width;
    int _height;

    bool _scaleWithScreenSize;
};
#endif
