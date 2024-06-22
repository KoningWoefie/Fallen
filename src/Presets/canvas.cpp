#include "src/UI/canvas.h"
#include <src/Presets/canvas.h>

namespace Presets
{
    Canvas::Canvas(int width, int height)
    {
        FallenUI::Canvas* c = new FallenUI::Canvas(width, height);
        this->transform->position = glm::vec3(c->GetCanvasWidth()/2, c->GetCanvasHeight()/2, 0);
        this->AddComponent(c);
    }

    Canvas::Canvas(glm::vec2 referenceResolution)
    {
        FallenUI::Canvas* c = new FallenUI::Canvas(referenceResolution);
        this->transform->position = glm::vec3(c->GetCanvasWidth()/2, c->GetCanvasHeight()/2, 0);
        this->AddComponent(c);
    }

    Canvas::~Canvas()
    {
    }

    void Canvas::Update(float deltaTime)
    {

    }
}
