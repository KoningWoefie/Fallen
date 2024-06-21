#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

#include <src/Core/config.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(int width, int height);
    virtual ~Mesh();

    //make rectangle and or square mesh
    void GenerateMesh(glm::vec2 pivot, float uvWidth, float uvHeight, bool nineSlice = false);
    void GenerateTextMesh(glm::vec2 pivot, float uvWidth, float uvHeight);

    //make circle mesh
    void GenerateCircleMesh(glm::vec2 pivot, float uvWidth, float uvHeight, int segments);

    //generate the buffers for openGL
    void GenerateBuffers(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs);

    GLuint GetVertexBuffer() { return _vertexbuffer; };
    GLuint GetUVBuffer() { return _uvbuffer; };

    glm::vec2 UV() { return _uv; };

    int GetNumverts() { return _numverts; };
private:
    int _width;
    int _height;
    int _numverts;
    int _radius;

    glm::vec2 _uv;

    GLuint _vertexbuffer;
    GLuint _uvbuffer;

    std::vector<glm::vec2> _uvs;
};

#endif
