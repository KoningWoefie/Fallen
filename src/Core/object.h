#ifndef OBJECT_H
#define OBJECT_H

#include <src/Core/inputmanager.h>
#include <iostream>
#include <vector>

#include <src/Core/transform.h>

class Object
{
public:
    Object();
    virtual ~Object();
    virtual void Update(float deltaTime) = 0;

    void AddChild(Object* child);
    void RemoveChild(Object* child);

    Object* GetChild(int index) { return m_children[index]; };

    std::vector<Object*> GetChildren() { return m_children; };

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    template <typename T>
    T* GetComponent()
    {
        for(int i = 0; i < m_components.size(); i++)
        {
            auto& type = *m_components[i];
            if(typeid(T) == typeid(type))
            {
                return dynamic_cast<T*>(m_components[i]);
            }
        }
        return nullptr;
    }


    std::vector<Component*> GetComponents() { return m_components; };

    Object* parent;

    Transform* transform;

protected:
    InputManager* Input() { return _input; }
private:
    std::vector<Object*> m_children;

    std::vector<Component*> m_components;

    InputManager* _input = InputManager::input();
};

#endif
