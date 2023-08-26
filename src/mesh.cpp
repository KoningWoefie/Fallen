#include <src/mesh.h>

Mesh::Mesh(int width, int height)
{
    _width = width;
    _height = height;

    _radius = 0;

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

    _numverts = 6;

    generateBuffers(vertices, _uvs);
}

void Mesh::generateCircleMesh(glm::vec2 pivot, float uvWidth, float uvHeight, int segments)
{
    _radius = _width / 2;
    unsigned int step = segments;
	_numverts = step*3; // n triangles with 3 vertices each
    float angle = (2.0f * PI) / step;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
    float rad = 2 * PI;
	// for each triangle, do ...
	for (unsigned int i = 0; i < step; i++) {
		// ####################################################
		// start at, and always go back to (0,0), UV (0.5,0.5)
		vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		uvs.push_back(glm::vec2(0.5f, 0.5f));

		// #############################
		// create second vertex
		x = cos(rad)*_radius;
		y = sin(rad)*_radius;
		u = (x/_radius) * uvWidth;
		v = (-y/_radius) * uvHeight;
		vertices.push_back(glm::vec3(x, y, 0.0f));
		uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)

		// #############################
		// rotate n degrees for the final vertex
		rad -= 2*PI/step;
		// create third vertex
		x = cos(rad)*_radius;
		y = sin(rad)*_radius;
		u = (x/_radius) * uvWidth;
		v = (-y/_radius) * uvHeight;
		vertices.push_back(glm::vec3(x, y, 0.0f));
		uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)
		// ####################################################
	}

	this->generateBuffers(vertices, uvs);
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