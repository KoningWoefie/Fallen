#ifndef CANVASPRESETS_H
#define CANVASPRESETS_H

#include <src/Core/object.h>
#include <src/UI/canvas.h>

namespace Presets
{
    class Canvas : public Object
    {
    public:
        Canvas(int width, int height);
        Canvas(glm::vec2 referenceResolution);

        virtual ~Canvas();

        virtual void Update(float deltaTime);
    };
}

#endif // CANVASPRESETS_H
