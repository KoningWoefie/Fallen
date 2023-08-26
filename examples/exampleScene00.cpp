#include "exampleScene00.h"

ExampleScene00::ExampleScene00()
{
    // _texturePath = "assets/RunButton.tga";
    _width = 200;
    _height = 200;

    _radius = 1;

    position = glm::vec3(200.0f, 300.0f, 0.0f);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::update(float deltaTime)
{
}