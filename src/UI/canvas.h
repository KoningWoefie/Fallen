#ifndef CANVAS_H
#define CANVAS_H

#include "src/Core/config.h"
#include <src/Core/component.h>

namespace FallenUI
{
    class Canvas : public Component
    {
    public:
        // Constructor that does not scale with screen size
        Canvas(int width, int height);

        // Constructor that scales with screen size according to the reference resolution
        Canvas(glm::vec2 referenceResolution);

        virtual ~Canvas();

        glm::vec2 GetCanvasSize() { return glm::vec2(_width, _height); };

        int GetCanvasWidth() { return _width; };
        int GetCanvasHeight() { return _height; };

        void SetCanvasSize(int width, int height) { _width = width; _height = height; };

        void SetCanvasWidth(int width) { _width = width; };
        void SetCanvasHeight(int height) { _height = height; };

        void SetScaleWithScreenSize(bool scale) { _scaleWithScreenSize = scale; };
        bool GetScaleWithScreenSize() { return _scaleWithScreenSize; };

        glm::vec2 GetReferenceResolution() { return _referenceResolution; };

    private:
        int _width;
        int _height;

        glm::vec2 _referenceResolution;

        bool _scaleWithScreenSize;
    };
}
#endif
