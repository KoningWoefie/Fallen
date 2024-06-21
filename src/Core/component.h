#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <glm/glm.hpp>
#include <iostream>

class Object;

class Component
{
public:
    Component();
    virtual ~Component();

    Object* GetObject() { return object; };

    bool isRenderable() { return Renderable; };
private:
    Object* object;
    friend class Object;
protected:
    bool Renderable;
};

#endif
