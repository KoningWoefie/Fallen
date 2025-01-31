#include <src/Core/color.h>
#include <iostream>

const glm::vec4 Color::White = glm::vec4(1, 1, 1, 1);
const glm::vec4 Color::Black = glm::vec4(0, 0, 0, 1);
const glm::vec4 Color::Red = glm::vec4(1, 0, 0, 1);
const glm::vec4 Color::Green = glm::vec4(0, 1, 0, 1);
const glm::vec4 Color::Blue = glm::vec4(0, 0, 1, 1);
const glm::vec4 Color::Orange = glm::vec4(1, 0.647f, 0, 1);
const glm::vec4 Color::Purple = glm::vec4(0.5f, 0, 0.5f, 1);
const glm::vec4 Color::Gray = glm::vec4(0.5f, 0.5f, 0.5f, 1);
const glm::vec4 Color::Grey = glm::vec4(0.5f, 0.5f, 0.5f, 1);
const glm::vec4 Color::Yellow = glm::vec4(1, 1, 0, 1);

glm::vec4 Color::RGBColor(char r, char g, char b)
{
    return glm::vec4(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}

glm::vec4 Color::RGBAColor(char r, char g, char b, char a)
{
    return glm::vec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

glm::vec4 Color::BGRColor(char b, char g, char r)
{
    return glm::vec4(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}

glm::vec4 Color::BGRAColor(char b, char g, char r, char a)
{
    return glm::vec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

glm::vec4 Color::HexCodeColor(std::string hexCode)
{
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    // Red
    if(hexCode[0] - 48 >= 0 && hexCode[0] < 58) r += (hexCode[0] - 48) * 16;
    else if (hexCode[0] - 65 >= 0 && hexCode[0] < 71) r += (hexCode[0] - 64 + 9) * 16;

    if(hexCode[1] - 48 >= 0 && hexCode[1] < 58) r += hexCode[1] - 48;
    else if (hexCode[1] - 65 >= 0 && hexCode[1] < 71) r += (hexCode[1] - 64 + 9);

    // Green
    if(hexCode[2] - 48 >= 0 && hexCode[2] < 58) g += (hexCode[2] - 48) * 16;
    else if (hexCode[2] - 65 >= 0 && hexCode[2] < 71) g += (hexCode[2] - 64 + 9) * 16;

    if(hexCode[3] - 48 >= 0 && hexCode[3] < 58) g += hexCode[3] - 48;
    else if (hexCode[3] - 65 >= 0 && hexCode[3] < 71) g += (hexCode[3] - 64 + 9);

    // Blue
    if(hexCode[4] - 48 >= 0 && hexCode[4] < 58) b += (hexCode[4] - 48) * 16;
    else if (hexCode[4] - 65 >= 0 && hexCode[4] < 71) b += (hexCode[4] - 64 + 9) * 16;

    if(hexCode[5] - 48 >= 0 && hexCode[5] < 58) b += hexCode[5] - 48;
    else if (hexCode[5] - 65 >= 0 && hexCode[5] < 71) b += (hexCode[5] - 64 + 9);

    return glm::vec4(r/255.0f,g/255.0f,b/255.0f,1);
}
