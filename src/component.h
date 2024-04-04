#ifndef COMPONENT_H
#define COMPONENT_H

class Object;

class Component
{
public:
    Component();
    virtual ~Component();

    Object* object;
private:
};

#endif
