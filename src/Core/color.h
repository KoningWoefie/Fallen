#ifndef COLOR_H
#define COLOR_H

#include <glm/glm.hpp>
#include <string>

class Color
{
public:

    static const glm::vec4 White;
    static const glm::vec4 Black;
    static const glm::vec4 Red;
    static const glm::vec4 Green;
    static const glm::vec4 Blue;
    static const glm::vec4 Orange;
    static const glm::vec4 Purple;
    static const glm::vec4 Gray;
    static const glm::vec4 Grey;
    static const glm::vec4 Yellow;

    static glm::vec4 RGBColor(char r, char g, char b);
    static glm::vec4 BGRColor(char b, char g, char r);
    static glm::vec4 RGBAColor(char r, char g, char b, char a);
    static glm::vec4 BGRAColor(char b, char g, char r, char a);
    static glm::vec4 HexCodeColor(std::string hexCode);

private:
};

#endif
