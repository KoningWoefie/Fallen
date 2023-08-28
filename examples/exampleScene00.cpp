#include "exampleScene00.h"

ExampleScene00::ExampleScene00()
{
    // _texturePath = "assets/RunButton.tga";
    _width = 200;
    _height = 200;

    _radius = 1;

    position = glm::vec3(200.0f, 300.0f, 0.0f);

    color = glm::vec4(0,0,255,255);

    st = new SheetTest("assets/Sprite_Sheet_G4.tga", 4, 4, 1.0f);
    this->AddChild(st);
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::update(float deltaTime)
{
    if(Input()->getKey(KeyCode::Right))
    {
        position.x += 100.0f * deltaTime;
    }
}