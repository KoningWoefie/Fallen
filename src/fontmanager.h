#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <string>
#include <map>
#include <iostream>

#include <glm/glm.hpp>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

struct glyph
{
    GLuint texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class FontManager
{
public:
    FontManager();
    ~FontManager();

    // Get the font
    std::map<char, glyph*> getFont(const char * fontPath, int size);

    // Make the font
    void addFont(const char * fontPath, int size);

private :
    std::map<const char *, int> _fontSizes;
    std::map<std::pair<const char *, int>, std::map<char, glyph*>> _fonts;
};

#endif