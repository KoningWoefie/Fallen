#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(int width, int height);
    virtual ~Mesh();

    //make rectangle and or square mesh
    void generateMesh(glm::vec2 pivot, float uvWidth, float uvHeight);

    //generate the buffers for openGL
    void generateBuffers(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs);

    GLuint vertexbuffer() { return _vertexbuffer; };
    GLuint uvbuffer() { return _uvbuffer; };
private:
    int _width;
    int _height;

    GLuint _vertexbuffer;
    GLuint _uvbuffer;

    std::vector<glm::vec2> _uvs;
};

#endif