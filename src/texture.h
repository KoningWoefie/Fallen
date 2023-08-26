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

    GLuint loadTGA(const std::string& path);

    GLuint getTexture() { return _texture; }

    int Width() { return _width; }
    int Height() { return _height; }
private:
    int _width;
    int _height;

    GLuint _texture;
};

#endif