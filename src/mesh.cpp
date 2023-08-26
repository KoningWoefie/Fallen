#include <src/mesh.h>

Mesh::Mesh(int width, int height)
{
    _width = width;
    _height = height;

    std::cout << _width << ", " << _height << std::endl;
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_vertexbuffer);
    glDeleteBuffers(1, &_uvbuffer);
}

void Mesh::generateMesh(glm::vec2 pivot, float uvWidth, float uvHeight)
{
    std::vector<glm::vec3> vertices;
    //first triangle
    vertices.push_back(glm::vec3(_width - (pivot.x * _width), -pivot.y * _height, 0.0f));
	vertices.push_back(glm::vec3(-pivot.x * _width, -pivot.y * _height, 0.0f));
	vertices.push_back(glm::vec3(-pivot.x * _width,  _height - (pivot.y * _height), 0.0f));
	// second triangle
	vertices.push_back(glm::vec3(-pivot.x * _width,  _height - (pivot.y * _height), 0.0f));
	vertices.push_back(glm::vec3(_width - (pivot.x * _width), _height - (pivot.y * _height), 0.0f));
	vertices.push_back(glm::vec3(_width - (pivot.x * _width), -pivot.y * _height, 0.0f));

    _uvs.push_back(glm::vec2(uvWidth, uvHeight));
	_uvs.push_back(glm::vec2(0.0f, uvHeight));
	_uvs.push_back(glm::vec2(0.0f, 0.0f));

	_uvs.push_back(glm::vec2(0.0f, 0.0f));
	_uvs.push_back(glm::vec2(uvWidth, 0.0f));
	_uvs.push_back(glm::vec2(uvWidth, uvHeight));

    generateBuffers(vertices, _uvs);
}

void Mesh::generateBuffers(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs)
{
    glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Send UV's to GPU
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}