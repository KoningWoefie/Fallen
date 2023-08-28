#include <src/dynamic.h>

Dynamic::Dynamic()
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    this->rotation = 0.0f;
    this->color = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
    _uvOffset = glm::vec2(0.0f,0.0f);

    this->parent = nullptr;

    _width = 0;
    _height = 0;

    _radius = 0;

    _texturePath = "";
}

Dynamic::~Dynamic()
{
    for (Dynamic* child : this->_children)
    {
        delete child;
        child = nullptr;
    }
}

void Dynamic::AddChild(Dynamic* child)
{
    if(child->parent != nullptr)
    {
        child->parent->RemoveChild(child);
    }
    _children.push_back(child);
    child->parent = this;
}

void Dynamic::RemoveChild(Dynamic* child)
{
    for (int i = 0; i < _children.size(); i++)
    {
        if(_children[i] != child)
        {
            continue;
        }
        _children.erase(_children.begin() + i);
        return;
    }
    std::cout << "Child not found" << std::endl;
}