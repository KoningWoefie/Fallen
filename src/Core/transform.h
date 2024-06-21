#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <src/Core/component.h>

class Transform : public Component
{
public:
    glm::vec3 position;
    float rotation;
    glm::vec3 scale;
private:
    Transform();
    virtual ~Transform();

    friend class Object;
};

#endif
