#ifndef IMAGE_H
#define IMAGE_H

#include <src/Core/sprite.h>
#include <glm/glm.hpp>

namespace Components
{
    class Image : public Component
    {
    public:
        Image();
        virtual ~Image();

        void AddSprite(Sprite* sprite);
        Sprite* GetSprite() { return m_sprite; };

        glm::vec4 color;

        int width;
        int height;

        glm::vec2 pivot;
    private:
        Sprite* m_sprite;
    };
}

#endif
