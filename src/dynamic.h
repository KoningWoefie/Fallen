#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

class Dynamic
{
public:
    Dynamic();
    virtual ~Dynamic();

    virtual void update(float deltaTime) = 0;

    void AddChild(Dynamic* child);
    void RemoveChild(Dynamic* child);

    std::vector<Dynamic*> GetChildren() { return _children; };

    Dynamic* parent;

    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
private:
    std::vector<Dynamic*> _children;
};


#endif