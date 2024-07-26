#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#include <GL/glew.h>

class Texture
{
public:
    Texture(int width = 0, int height = 0);
    virtual ~Texture();

    GLuint LoadTGA(const std::string& path, unsigned char filter = 1);

    GLuint GetTexture() { return _texture; }

    int Width() { return _width; }
    int Height() { return _height; }
private:
    int _width;
    int _height;

    GLuint _texture;
};

#endif
