#include "src/component.h"
#include <src/image.h>

Image::Image() : Component()
{
    Renderable = true;

	m_sprite = nullptr;
	width = 0;
	height = 0;
	pivot = glm::vec2(0.5f, 0.5f);

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
