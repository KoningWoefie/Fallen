#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <glm/glm.hpp>
#include <src/Core/component.h>

// Doesn't need to have a cpp file
class Text : public Component
{
public:
    Text(char * fontPath = (char *)"fonts/Roboto-Regular.ttf", int size = 64) : Component() { _font = fontPath; _size = size; Renderable = true; };
    ~Text() {};

    char * GetFontName() { return _font; }
    int GetSize() { return _size; }

    glm::vec2 pivot = glm::vec2(0.0f, 0.0f);

    glm::vec4 color = glm::vec4(255, 255, 255, 255);
    std::string text;
    bool centered = false;

private:
    char * _font;
    int _size;

};

#endif
