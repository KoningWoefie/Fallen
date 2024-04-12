#ifndef BUTTON_H
#define BUTTON_H

#include <src/component.h>

class Button : public Component
{
public:
    Button();
    Button(int width, int height);
    virtual ~Button();

    int GetWidth() { return _width; }
    int GetHeight() { return _height; }
    glm::vec2 GetSize() { return glm::vec2(_width, _height); }

    void SetSize(int width, int height) { _width = width; _height = height; };
private:
    int _width;
    int _height;
};

#endif
