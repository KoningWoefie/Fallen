#include <src/object.h>

Object::Object()
{
    transform = new Transform(this);
    AddComponent(transform);
}

Object::~Object()
{

}

void Object::Update(float deltaTime)
{
}

void Object::AddChild(Object* child)
{
    m_children.push_back(child);
}

void Object::RemoveChild(Object* child)
{
    for(int i = 0; i < m_children.size(); i++)
    {
        if(m_children[i] == child)
        {
            m_children.erase(m_children.begin() + i);
            return;
        }
    }
    std::cout << "Child not found" << std::endl;
}

void Object::AddComponent(Component* component)
{
    m_components.push_back(component);
}

void Object::RemoveComponent(Component* component)
{
    if(component == transform)
    {
        std::cout << "Cannot remove transform component" << std::endl;
        return;
    }
    for(int i = 0; i < m_components.size(); i++)
    {
        if(m_components[i] == component)
        {
            m_components.erase(m_components.begin() + i);
            return;
        }
    }
    std::cout << "Component not found" << std::endl;
}

template<class T>
T* Object::GetComponent()
{
    for(int i = 0; i < m_components.size(); i++)
    {
        if(typeid(T*) == typeid(m_components[i]))
        {
            return dynamic_cast<T*>(m_components[i]);
        }
    }

    std::cout << "Component not found" << std::endl;
    return nullptr;
}
