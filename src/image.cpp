#include "src/component.h"
#include <src/image.h>

Image::Image() : Component()
{
    Renderable = true;

    color = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
}

Image::~Image()
{
    //dtor
}

void Image::AddSprite(Sprite *sprite)
{
    if(m_sprite != nullptr)
    {
        delete m_sprite;
        m_sprite = nullptr;
    }

    m_sprite = sprite;
}
