#include <src/Core/transform.h>

Transform::Transform()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = 0.0f;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

}

Transform::~Transform()
{
    // dtor
}
