#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include <src/config.h>

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

    glm::vec4 color;

    std::string FileName() { return _texturePath; }

    int Width() { return _width; }
    int Height() { return _height; }
    int Radius() { return _radius; }
private:
    std::vector<Dynamic*> _children;
protected:
    int _width;
    int _height;
    int _radius;

    std::string _texturePath;
};


#endif