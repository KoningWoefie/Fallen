#include "src/UI/canvas.h"
#include "src/Core/transform.h"
#include "src/UI/uielement.h"
#include <src/Core/object.h>

Object::Object()
{
    transform = new Transform();
    AddComponent(transform);
}

Object::~Object()
{

}

void Object::AddChild(Object* child)
{
    if(this->GetComponent<Components::Canvas>() || this->GetComponent<Components::UIElement>())
    {
        if(!child->GetComponent<Components::Canvas>() && !child->GetComponent<Components::UIElement>()) child->AddComponent(new Components::UIElement());
    }
    m_children.push_back(child);
    child->parent = this;
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
    std::cout << "Child not found" << "\n";
}

void Object::AddComponent(Component* component)
{
    m_components.push_back(component);
    component->object = this;
}

void Object::RemoveComponent(Component* component)
{
    if(component == transform)
    {
        std::cout << "Cannot remove transform component" << "\n";
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
    std::cout << "Component not found" << "\n";
}
