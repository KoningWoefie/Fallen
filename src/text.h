#ifndef TEXT_H
#define TEXT_H

#include <string>

#include <glm/glm.hpp>

// Doesn't need to have a cpp file
class Text
{
public:
    Text(char * fontPath, int size) { _font = fontPath; _size = size; };
    ~Text() {};

    std::string GetMessage() { return _message; };
    void Message(std::string message) { _message = message; };

    char * GetFontName() { return _font; }
    int GetSize() { return _size; }

    glm::vec4 color = glm::vec4(255, 255, 255, 255);

private:
    char * _font;
    int _size;

    std::string _message;
};

#endif