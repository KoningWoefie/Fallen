#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <src/component.h>

class Transform : public Component
{
public:
    glm::vec3 position;
    float rotation;
    glm::vec3 scale;
private:
    Transform(Object* obj);
    virtual ~Transform();

    friend class Object;
};

#endif
