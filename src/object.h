#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include <src/transform.h>

class Object
{
public:
    Object();
    ~Object();
    virtual void Update(float deltaTime);

    void AddChild(Object* child);
    void RemoveChild(Object* child);

    Object* GetChild(int index) { return m_children[index]; };

    std::vector<Object*> GetChildren() { return m_children; };

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    template <typename T>
    T* GetComponent();

    Object* parent;

    Transform* transform;
private:
    std::vector<Object*> m_children;

    std::vector<Component*> m_components;
};

#endif
